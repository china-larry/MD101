#ifndef CMQTT2CANTHREAD_H
#define CMQTT2CANTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "PublicConfig.h"
class CMqtt2CanThread : public QThread
{
    Q_OBJECT

public:
    explicit CMqtt2CanThread();
    ~CMqtt2CanThread();

protected:
    virtual void run();

signals:
    void SignalOneSubscribeMsg(SMqttMsgStruct strMsg);
public:
    static CMqtt2CanThread* GetInstance();
    //
    void AddSubscribeMsg(QString strTopic, QString strMsg);
private:
    static CMqtt2CanThread *sm_pInstance;

    QList<SMqttMsgStruct> m_strSubscribeMsgList;
    SMqttMsgStruct m_sCurrentSubscribeMsgStuct;
    QString m_strTopic;
    QStringList m_strTopicList;
    QString m_strMessage;
    QMutex m_qLockerMutex;
};

#endif // CMQTT2CANTHREAD_H
