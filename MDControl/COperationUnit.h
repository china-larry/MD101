#ifndef COPERATIONUNIT_H
#define COPERATIONUNIT_H

#include <QObject>
#include <QMutex>

#include "PublicConfig.h"
class COperationUnit : public QObject
{
    Q_OBJECT
public:
    explicit COperationUnit(QObject *parent = nullptr);
    ~COperationUnit();

signals:
    void SignalSendData(QByteArray qDataByteArray);
public slots:

public:
    void RunMotor(quint16 iSpeed, quint16 iSteps, quint8 iFlag);
public:
    //
    void SetDeviceOperate(bool bIsOperate);
    bool GetDeviceOperateStates();
    static COperationUnit* GetInstance();

private:
    static COperationUnit *sm_pInstance;

    QMutex m_DeviceOperateMutex;
    bool m_bIsDeviceOperate;//仪器是否在操作
    int m_iFrameNumber;

};

#endif // COPERATIONUNIT_H
