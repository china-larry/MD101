#ifndef CHISTORYDB_H
#define CHISTORYDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "PublicConfig.h"

class CHistoryDB : public QObject
{
    Q_OBJECT
public:
    explicit CHistoryDB(QObject *parent = nullptr);
    ~CHistoryDB();
signals:

public slots:
public:
    //获取类对象
    static CHistoryDB* GetInstance();
    //类对象
    static CHistoryDB* m_pInstance;
    void InitDataBase();
    //

private:
    QSqlDatabase m_qSqldb;
    int m_iDatabaseColumnCount;// 数据库项列数
    int m_iResultIndexCount;// 测试结果共计的相（只没个项目结果共计几组，当前为7，strProgramName, name, result,cutoff,t,c,t/c, controlline）
    int m_iMaxTestResult;// 当前允许的最大项目数，当前为20个

};

#endif // CHISTORYDB_H
