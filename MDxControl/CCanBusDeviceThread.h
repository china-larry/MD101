#ifndef CCANBUSDEVICETHREAD_H
#define CCANBUSDEVICETHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QCanBusDevice>
#include <QTime>
#include "PublicConfig.h"
class CCanBusDeviceThread : public QThread
{

    Q_OBJECT
public:
   explicit CCanBusDeviceThread();
    ~CCanBusDeviceThread();

protected:
    virtual void run();

signals:
    void SignalConnectError(QString strInterfaceName, QString strErrorCode);
    void SignalReadFramePayload(QByteArray qPayload);
public slots:
//    void SlotReadOneMqttMsg(SMqttMsgStruct strMsgStruct);
    void SlotCanBusError(QCanBusDevice::CanBusError error);
    void SlotCanFramesReceived();
public:
    bool InitCanBusDevice(const SCanBusDeviceStruct sSCanBusDeviceStruct);
    void SendPortData(QByteArray qDataByteArray);
    SCanBusDeviceStruct GetCanBusInfo();
    void AddSendData(SCanBusDataStruct &sSCanBusDataStruct);
    void SetWaitACK(bool bWaitACK);
private:
    QByteArray _GetSendData(SCanBusDataStruct &sSCanBusDataStruct);
    void _SendFrameData(QByteArray qPortDataByteArray);
public:
    static CCanBusDeviceThread* GetInstance();
private:
    static CCanBusDeviceThread *sm_pInstance;
    QCanBusDevice *m_pCanBusDevice;
    SCanBusDeviceStruct m_sSCanBusDeviceStruct;
    QMutex m_qLockerMutex;
    QCanBusFrame m_qFrameForSend;
    QCanBusFrame m_qFrameForRead;
    QList<QByteArray> m_qSendPortDataList;
    QByteArray m_qCurrentPortDataByteArray;
    QByteArray m_qReadFrameByteArray;
    int m_iReSendTimes;// can 发送是否成功，决定是否发送下一帧
    bool m_bWaitAck;
    QTime m_qCurrentSendTime;// send time
    int m_iWaitMsecsTo;
    // read
    bool m_bFramesAvailableBuffer;
    //
    int m_iTotalFrameNumbers;
    int m_iLastFrameCount;
    quint16 m_iFrameNumber;
};

#endif // CCANBUSDEVICETHREAD_H
