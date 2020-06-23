#include "CMqtt2CanThread.h"
#include <QDebug>
#include "COperationUnit.h"
CMqtt2CanThread* CMqtt2CanThread::sm_pInstance = new CMqtt2CanThread();

CMqtt2CanThread::CMqtt2CanThread()
{
    qRegisterMetaType<SMqttMsgStruct>("SMqttMsgStruct");
}

CMqtt2CanThread::~CMqtt2CanThread()
{
    if(sm_pInstance != NULL)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }
}

CMqtt2CanThread* CMqtt2CanThread::GetInstance()
{
    return sm_pInstance;
}

void CMqtt2CanThread::run()
{
    while(true)
    {
        if(m_strSubscribeMsgList.count() > 0)
        {
            m_qLockerMutex.lock();
            m_sCurrentSubscribeMsgStuct = m_strSubscribeMsgList.at(0);
            m_strSubscribeMsgList.pop_front();
            m_qLockerMutex.unlock();
            qDebug() << "amtt 2 can msg 55" << m_sCurrentSubscribeMsgStuct.strMessage;
            m_strTopic = m_sCurrentSubscribeMsgStuct.strTopic;
            m_strMessage = m_sCurrentSubscribeMsgStuct.strMessage;
            m_strTopicList = m_strTopic.split("/");
            qDebug() << "topic list" << m_strTopicList;

            if(m_strTopicList.count() > 0)
            {
                COperationUnit::GetInstance()->RunMotor(2,2,2);
            }

        }
        msleep(100);
    }
}

void CMqtt2CanThread::AddSubscribeMsg(QString strTopic, QString strMsg)
{
    SMqttMsgStruct sSMqttMsgStruct;
    sSMqttMsgStruct.strTopic = strTopic;
    sSMqttMsgStruct.strMessage = strMsg;
    m_qLockerMutex.lock();
    m_strSubscribeMsgList.push_back(sSMqttMsgStruct);
    m_qLockerMutex.unlock();
}
