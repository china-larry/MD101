#include "CCanBusDeviceThread.h"
#include <QCanBus>
#include <QVariant>
#include <QDebug>
#include <QDataStream>
#include "PublicFunction.h"
// 饿汉模式，多线程安全
CCanBusDeviceThread * CCanBusDeviceThread::sm_pInstance = new CCanBusDeviceThread();

CCanBusDeviceThread::CCanBusDeviceThread()
{
    qRegisterMetaType<QCanBusDevice::CanBusError>("QCanBusDevice::CanBusError");
    m_pCanBusDevice = NULL;
    m_iReSendTimes = gk_iReSendTimes;// 重发3次
    m_iFrameNumber = 0;
}

CCanBusDeviceThread::~CCanBusDeviceThread()
{
    if(sm_pInstance != NULL)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }
}

CCanBusDeviceThread *CCanBusDeviceThread::GetInstance()
{
    return sm_pInstance;
}
void CCanBusDeviceThread::_SendFrameData(QByteArray qPortDataByteArray)
{
    m_iTotalFrameNumbers = qPortDataByteArray.length() / 8;
    m_iLastFrameCount = qPortDataByteArray.length() % 8;
    qDebug() << "----------------------------------send frame "
             << QTime::currentTime().toString("hh:mm:ss:zzz")
             << qPortDataByteArray;
//            m_qFrameForSend.setFrameId(m_sSCanBusDeviceStruct.iFrameId);
    for(int i = 0; i < m_iTotalFrameNumbers; ++i)
    {
        m_qFrameForSend.setPayload(qPortDataByteArray.mid(i*8, 8));
        if(!m_pCanBusDevice->writeFrame(m_qFrameForSend))
        {
            qDebug() << "write fram error" << m_pCanBusDevice->errorString();
        }
    }
    if(m_iLastFrameCount)
    {
        m_qFrameForSend.setPayload(qPortDataByteArray.mid(m_iTotalFrameNumbers*8, m_iLastFrameCount));
        if(!m_pCanBusDevice->writeFrame(m_qFrameForSend))
        {
            qDebug() << "write fram error" << m_pCanBusDevice->errorString();
        }
    }
}
void CCanBusDeviceThread::run()
{
    m_bWaitAck = false;
    while(m_pCanBusDevice != NULL)
    {
        if(m_bWaitAck)
        {
            m_iWaitMsecsTo = m_qCurrentSendTime.msecsTo(QTime::currentTime());
            if(m_iReSendTimes > gk_iReSendTimes)
            {// ACK 超时
                m_qLockerMutex.lock();
                m_bWaitAck = false;
                m_iReSendTimes = 0;
                m_qLockerMutex.unlock();
                // emit
                qDebug() << "***************** ACK 超时";
            }
            else
            {
                if(m_iWaitMsecsTo > gk_iWaitMsecs)
                {//  重发
                    qDebug() << "*****************Re Send " << m_iReSendTimes;
                    _SendFrameData(m_qCurrentPortDataByteArray);
                    m_qLockerMutex.lock();
                    m_qCurrentSendTime = QTime::currentTime();
                    m_iReSendTimes++;
                    m_qLockerMutex.unlock();
                }
            }
        }
        else
        {
            if(m_qSendPortDataList.count() > 0)
            {
                m_qCurrentPortDataByteArray = m_qSendPortDataList[0];
                _SendFrameData(m_qCurrentPortDataByteArray);
                m_qLockerMutex.lock();
                m_qCurrentSendTime = QTime::currentTime();
                m_bWaitAck = true;
                m_iReSendTimes = 0;
                m_qSendPortDataList.pop_front();
                m_qLockerMutex.unlock();
            }
        }

        if(m_bFramesAvailableBuffer)
        {
//            qDebug() << "current frames available " << m_pCanBusDevice->framesAvailable();
            m_qReadFrameByteArray = "";
            while(m_pCanBusDevice->framesAvailable())
            {
                m_qFrameForRead = m_pCanBusDevice->readFrame();
                m_qReadFrameByteArray += m_qFrameForRead.payload();
            }
            emit SignalReadFramePayload(m_qReadFrameByteArray);
            m_bFramesAvailableBuffer = false;
        }
        msleep(100);
    }
}

//void CCanBusDeviceThread::SlotReadOneMqttMsg(SMqttMsgStruct strMsgStruct)
//{
//    qDebug() << "get read one mqtt msg" << strMsgStruct.strMessage;
////    QString strNewTmp = strMsg.replace(QRegExp("/"), "+");
////    QStringList strMsgList = strMsg.split("+");
//    qDebug() << "str Msg List " << strMsgStruct.strMessage;
//    // 分拆发送Can
//    m_qLockerMutex.lock();
//    m_iSendTimes = gk_iReSendTimes;
//    m_qSendPortDataList.push_back(strMsgStruct.strMessage.toUtf8());
//    m_qLockerMutex.unlock();
//}

void CCanBusDeviceThread::SlotCanBusError(QCanBusDevice::CanBusError error)
{
    qDebug() << "CanBus Error 000" << error;
}

void CCanBusDeviceThread::SlotCanFramesReceived()
{
//    qDebug() << "SlotCanFramesReceived ";
    m_qLockerMutex.lock();
    m_bFramesAvailableBuffer = true;
    m_qLockerMutex.unlock();
}

bool CCanBusDeviceThread::InitCanBusDevice(const SCanBusDeviceStruct sSCanBusDeviceStruct)
{
    m_sSCanBusDeviceStruct = sSCanBusDeviceStruct;
    QString strErrorString;
    m_pCanBusDevice = QCanBus::instance()->createDevice(
          m_sSCanBusDeviceStruct.strPlugin, m_sSCanBusDeviceStruct.strInterfaceName, &strErrorString);
    if (!m_pCanBusDevice)
    {
        qDebug() << "bade" << strErrorString;
        emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, strErrorString);
        return false;
    }
    qDebug() << "good create";
    connect(m_pCanBusDevice, &QCanBusDevice::errorOccurred, this, &CCanBusDeviceThread::SlotCanBusError);
    connect(m_pCanBusDevice, &QCanBusDevice::framesReceived, this, &CCanBusDeviceThread::SlotCanFramesReceived);
    m_pCanBusDevice->setConfigurationParameter(QCanBusDevice::BitRateKey,m_sSCanBusDeviceStruct.iBitRate);
    qDebug() << "fream connectDevice";
    if(!m_pCanBusDevice->connectDevice())
    {
        emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, m_pCanBusDevice->errorString());
        delete m_pCanBusDevice;
        m_pCanBusDevice = NULL;
        return false;
    }
    else
    {
        QVariant qBitRate = m_pCanBusDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (qBitRate.isValid())
        {
            qDebug() << (QString("11 Backend: %1, connected to %2 at %3 kBit/s")
                    .arg(m_sSCanBusDeviceStruct.strPlugin).arg(m_sSCanBusDeviceStruct.strInterfaceName)
                    .arg(qBitRate.toInt()/1000));
            return true;
        }
        else
        {
            emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, "bad BitRate");
            delete m_pCanBusDevice;
            m_pCanBusDevice = NULL;
            return false;
        }
    }
    return true;
}

void CCanBusDeviceThread::SendPortData(QByteArray qDataByteArray)
{
//    qDebug() << "get send prot "<< qDataByteArray;
    m_qLockerMutex.lock();
    m_qSendPortDataList.push_back(qDataByteArray);
    m_qLockerMutex.unlock();
}

SCanBusDeviceStruct CCanBusDeviceThread::GetCanBusInfo()
{
    return m_sSCanBusDeviceStruct;
}

void CCanBusDeviceThread::AddSendData(SCanBusDataStruct &sSCanBusDataStruct)
{
    m_iFrameNumber++;
    QByteArray qSendData = _GetSendData(sSCanBusDataStruct);
    SendPortData(qSendData);
}

void CCanBusDeviceThread::SetWaitACK(bool bWaitACK)
{
    m_qLockerMutex.lock();
    m_bWaitAck = bWaitACK;
    m_qLockerMutex.unlock();
}

QByteArray CCanBusDeviceThread::_GetSendData(SCanBusDataStruct &sSCanBusDataStruct)
{
    QByteArray qBlockByteArray;
    QDataStream qOutDataStream
            (&qBlockByteArray,QIODevice::ReadWrite);
    qOutDataStream.setByteOrder(QDataStream::LittleEndian);  //设置xiao端格式

    qOutDataStream << quint16(0x4D40)
                   << quint16(0x7844)
                   << quint16(0x0401)
                   << sSCanBusDataStruct.quCmdID
                   << sSCanBusDataStruct.quObjectID
                   << sSCanBusDataStruct.quErrorID
                   << sSCanBusDataStruct.quFormat
                   << m_iFrameNumber
                   << quint16(0x0000)
                   << quint16(sSCanBusDataStruct.qbPayload.count());
    //qOutDataStream << sSCanBusDataStruct.qbPayload;
    qBlockByteArray += sSCanBusDataStruct.qbPayload;

    qOutDataStream.device()->seek(16+sSCanBusDataStruct.qbPayload.count());
    //添加CRC16
    quint16 iCrc16 = GetCRC16(qBlockByteArray.data(), qBlockByteArray.count(), 0);


    qOutDataStream << quint16(GetSmallByte(iCrc16));
    //修改帧长度
   //

    qDebug()<<" ---------------------------------send " << qBlockByteArray.toHex();
    return qBlockByteArray;
}


