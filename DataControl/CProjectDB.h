#ifndef CPROJECTDB_H
#define CPROJECTDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class CProjectDB : public QObject
{
    Q_OBJECT
public:
    explicit CProjectDB(QObject *parent = nullptr);
    ~CProjectDB();
signals:

public slots:
public:
    //获取类对象
    static CProjectDB* GetInstance();
    //类对象
    static CProjectDB* m_pInstance;
    void InitDataBase();
    //

private:
    void _InitCardInfoDB();
    void _InitSampleInfoDB();
    void _InitPersonInfoDB();
    //


private:
    QSqlDatabase m_qSqldb;
};

#endif // CPROJECTDB_H
