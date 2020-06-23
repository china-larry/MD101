#include "CAnalyzeCanMsgThread.h"
#include <QDateTime>
#include <QDebug>
#include "CCanBusDeviceThread.h"
#include "PublicFunction.h"
//
// 饿汉模式，多线程安全
CAnalyzeCanMsgThread * CAnalyzeCanMsgThread::sm_pInstance = new CAnalyzeCanMsgThread();
CAnalyzeCanMsgThread::CAnalyzeCanMsgThread()
{
    m_qbReadBuffArray = "";
}

CAnalyzeCanMsgThread::~CAnalyzeCanMsgThread()
{
    if(sm_pInstance != NULL)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }
}
CAnalyzeCanMsgThread *CAnalyzeCanMsgThread::GetInstance()
{
    return sm_pInstance;
}
void CAnalyzeCanMsgThread::run()
{
    while(true)
    {
        if(m_qCanMsgList.count() > 0)
        {
            m_qLockerMutex.lock();
            m_qbReadBuffArray += m_qCanMsgList.at(0);
            m_qLockerMutex.unlock();
            //
            m_iRedaBuffArrayLength = m_qbReadBuffArray.length();
            qDebug() << " +++++++++++++++++++++++++++++++read can msg "
                     << QTime::currentTime().toString("hh:mm:ss:zzz")
                     << m_iRedaBuffArrayLength << "  "
                     << "++\r\n" << m_qbReadBuffArray ;
            m_qCanMsgList.pop_front();
            while(m_iRedaBuffArrayLength >= 18)// 一帧至少长度为18
            {
                if(m_qbReadBuffArray[0] ==0x40 && m_qbReadBuffArray[1] ==0x4D
                        &&m_qbReadBuffArray[2] ==0x44 && m_qbReadBuffArray[3] ==0x78)
                {
                    //
                    pLength = m_qbReadBuffArray.data() + 10;
                    m_iReadSeqNumber = GetByte2Int(pLength);
                    //
                    pLength = m_qbReadBuffArray.data() + 14;
                    m_iReadFreamLength = GetByte2Int(pLength);
                    if(m_iRedaBuffArrayLength >= m_iReadFreamLength + 18)//18为除去payload的剩余帧长度
                    {
                        m_qPayloadByteArray = m_qbReadBuffArray.mid(16, m_iReadFreamLength);
                        qDebug()<< "+++++++++++++++++++++++++++++++ read frame  "
                                << QTime::currentTime().toString("hh:mm:ss:zzz")
                                << m_iReadSeqNumber << "___" << m_qbReadBuffArray.mid(0, m_iReadFreamLength+18)
                                << "payload date" << m_iReadFreamLength
                                << m_qbReadBuffArray.mid(16, m_iReadFreamLength);

                        if(m_qPayloadByteArray.contains("@MDx"))
                        {
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            qDebug() << "bad frame ***************************************";
                            int iNextFrame = m_qPayloadByteArray.indexOf("@MDx");
                            m_qbReadBuffArray = m_qbReadBuffArray.remove(0, 16 + iNextFrame);// 删除bad帧
                            m_iRedaBuffArrayLength = m_qbReadBuffArray.length();
                            break;
                        }

                        if(m_qbReadBuffArray[6] == 0x02)
                        {// ACK应答包
                            qDebug() << "+++iget ack data " << m_qbReadBuffArray[8];
                            if(m_qbReadBuffArray[8] == 0x00)
                            {
                                CCanBusDeviceThread::GetInstance()->SetWaitACK(false);
                            }
                        }
                        else if(m_qbReadBuffArray[6] == 0x03)
                        {// Reply

                        }
                        else if(m_qbReadBuffArray[6] == 0x04)
                        {// Notification

                        }
                        else
                        {

                        }
                        //
                        m_qbReadBuffArray = m_qbReadBuffArray.remove(0, m_iReadFreamLength+18);// 删除一帧
                        m_iRedaBuffArrayLength = m_qbReadBuffArray.length();
                        qDebug() << "read one finish\r\n";
                    }
                    else
                    {//等待足够的帧数据解析完整帧
                        qDebug() << "**********not one fream " << m_qbReadBuffArray;
                        break;
                    }
                }
                else
                {
                    qDebug() << "**********not @MDx " << m_qbReadBuffArray;
                    m_qbReadBuffArray = m_qbReadBuffArray.remove(0, 1);// 首字节不是@MDx，摒弃
                    m_iRedaBuffArrayLength = m_qbReadBuffArray.length();
                }
            }
        }
        msleep(100);
    }
}

void CAnalyzeCanMsgThread::SlotReadCanMsg(QByteArray qCanMsg)
{
   // m_iReadNumber += qCanMsg.length();
  //  qDebug() << "slot read can msg 3  " << qCanMsg << m_iReadNumber;

    m_qLockerMutex.lock();
    m_qCanMsgList.push_back(qCanMsg);
    m_qLockerMutex.unlock();

  //  qDebug() << "m_qCanMsgList count " << m_qCanMsgList.count();
}


