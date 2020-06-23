#include "COperationUnit.h"
#include <QDataStream>
#include "CCanBusDeviceThread.h"

COperationUnit* COperationUnit::sm_pInstance = new COperationUnit();

COperationUnit::COperationUnit(QObject *parent) : QObject(parent)
{
    m_iFrameNumber = 0;
}

COperationUnit::~COperationUnit()
{
    if(sm_pInstance != NULL)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }
}

void COperationUnit::RunMotor(quint16 iSpeed, quint16 iSteps, quint8 iFlag)
{
    SCanBusDataStruct sSCanBusDataStruct;
    sSCanBusDataStruct.quCmdID = 0x00;
    sSCanBusDataStruct.quObjectID = 0x00;
    sSCanBusDataStruct.quErrorID = 0X00;
    sSCanBusDataStruct.quFormat = 0x00;

    sSCanBusDataStruct.qbPayload = "{\"TEST\":\"GOODONE\"}";

    CCanBusDeviceThread::GetInstance()->AddSendData(sSCanBusDataStruct);
}

void COperationUnit::SetDeviceOperate(bool bIsOperate)
{
    m_DeviceOperateMutex.lock();
    m_bIsDeviceOperate = bIsOperate;
    m_DeviceOperateMutex.unlock();
}

bool COperationUnit::GetDeviceOperateStates()
{
    return m_bIsDeviceOperate;
}

COperationUnit *COperationUnit::GetInstance()
{
    return sm_pInstance;
}
