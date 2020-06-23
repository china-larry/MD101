#ifndef CANALYZECANMSGTHREAD_H
#define CANALYZECANMSGTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
class CAnalyzeCanMsgThread : public QThread
{
    Q_OBJECT

public:
    explicit CAnalyzeCanMsgThread();
    ~CAnalyzeCanMsgThread();

protected:
    virtual void run();

public slots:
    void SlotReadCanMsg(QByteArray qCanMsg);
public:
    static CAnalyzeCanMsgThread* GetInstance();
private:
    static CAnalyzeCanMsgThread *sm_pInstance;
    QMutex m_qLockerMutex;
    QByteArray m_qbReadBuffArray;
    int m_iRedaBuffArrayLength;
    int m_iReadFreamLength;
    QList<QByteArray> m_qCanMsgList;
    int m_iReadSeqNumber;
    //
    char *pLength;
    QByteArray m_qPayloadByteArray;
};

#endif // CANALYZECANMSGTHREAD_H
