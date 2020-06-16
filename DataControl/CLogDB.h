#ifndef CLOGDB_H
#define CLOGDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class CLogDB : public QObject
{
    Q_OBJECT
public:
    explicit CLogDB(QObject *parent = nullptr);
    ~CLogDB();
signals:


public:
    //获取类对象
    static CLogDB* GetInstance();
    //类对象
    static CLogDB* m_pInstance;
    void InitDataBase();

};

#endif // CLOGDB_H
