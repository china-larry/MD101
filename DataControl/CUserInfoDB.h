#ifndef CUSERINFODB_H
#define CUSERINFODB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "PublicConfig.h"
class CUserInfoDB : public QObject
{
    Q_OBJECT
public:
    explicit CUserInfoDB(QObject *parent = 0);
    ~CUserInfoDB();
signals:

public slots:
public:
    //获取类对象
    static CUserInfoDB* GetInstance();
    //类对象
    static CUserInfoDB* m_pInstance;
    void InitDataBase();
    //
    bool AddUserData(QStringList strListValue);
    bool DeleteUserData(QList<QString> strIDList);
    bool DeleteAllUserData();
    bool GetAllDataUserData(QVector<QStringList> &qAllDataVector);
    int FindUserID(QString strUserName);
    bool FindUserPassWord(QString strUserName, QString &strPassWord);
private:
    QSqlDatabase m_qSqldb;
    int m_iDBIndexCount;// 数据字段长度

};

#endif // CUSERINFODB_H
