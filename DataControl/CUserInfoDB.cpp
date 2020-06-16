#include "CUserInfoDB.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "PublicConfig.h"
#include "PublicFunction.h"
#include "CommonDataWidget/CMessageBox.h"
CUserInfoDB* CUserInfoDB::m_pInstance = new CUserInfoDB();
CUserInfoDB::CUserInfoDB(QObject *parent) : QObject(parent)
{
    m_iDBIndexCount = 5;// 不包括ID
}

CUserInfoDB::~CUserInfoDB()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CUserInfoDB *CUserInfoDB::GetInstance()
{
    return m_pInstance;
}

void CUserInfoDB::InitDataBase()
{
    m_qSqldb = ConnectDataBase(gc_strSystemDB, gc_strSystemDBConnect);
    if(m_qSqldb.isOpen() == false)
    {
        m_qSqldb.open();
    }
    if(m_qSqldb.isOpen())
    {
        QString strCreateTable  = "CREATE TABLE userdata ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "UserName VARCHAR,"
                                  "PassWord VARCHAR,"
                                  "UserType VARCHAR,"
                                  "CreateTime VARCHAR,"
                                  "Info VARCHAR)";

        //-qDebug() << "cread strCreateTable " << strCreateTable;
        // 创建
        QSqlQuery qSqlQuery(m_qSqldb);
        if (!qSqlQuery.exec(strCreateTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }
}

bool CUserInfoDB::AddUserData(QStringList strListValue)
{
    int iListCount = strListValue.count();
    if(iListCount != m_iDBIndexCount)
    {
        return false;
    }

    if(m_qSqldb.isOpen())
    {   // 查找是否已经存在
        QSqlQuery qSqlQuery(m_qSqldb);//
        QString strSelect = QString("SELECT * FROM userdata WHERE UserName = '")
                + strListValue[0] + "'";
        qSqlQuery.exec(strSelect);
        while(qSqlQuery.next())
        {
             ShowInformation(NULL, tr("Tip"), tr("Already exists in the database"), QMessageBox::Ok,QMessageBox::Ok);
            return false;
        }
        // 数据库插入
        qSqlQuery.prepare("INSERT INTO userdata (UserName,PassWord,UserType,CreateTime,Info) "
                          "VALUES (?,?,?,?,?)");
        for(int i = 0; i != m_iDBIndexCount; ++i)
        {
            qSqlQuery.addBindValue(strListValue[i]);
        }
        //
        if (!qSqlQuery.exec())
        {
            //-qDebug() << qSqlQuery.lastError();
            ShowWarning(NULL, tr("Warning"),
                                    tr("Database error"), QMessageBox::Ok,QMessageBox::Ok);
            return false;
        }
        qSqlQuery.finish();
        return true;
    }
    return false;
}

bool CUserInfoDB::DeleteUserData(QList<QString> strIDList)
{
    if(strIDList.count() < 0)
    {
        return false;
    }
    QString strID;

    QString strDelete;
    if(m_qSqldb.isOpen())
    {
        QSqlQuery qSqlQuery(m_qSqldb);
        for(int i = 0; i < strIDList.count(); ++i)
        {
            strID = strIDList.at(i);
            strDelete = "DELETE FROM userdata WHERE id = ";
            strDelete += strID;
            if (!qSqlQuery.exec(strDelete))
            {
                //-qDebug() << qSqlQuery.lastError();
                QMessageBox::warning(0, QObject::tr("删除失败"),
                                      qSqlQuery.lastError().text());
                qSqlQuery.finish();
                return false;
            }
        }
        qSqlQuery.finish();
    }
    return true;
}

bool CUserInfoDB::DeleteAllUserData()
{
    if(m_qSqldb.isOpen())
    {
        QString strdeleteTable  = "delete from userdata";
        // 创建
        QSqlQuery qSqlQuery(m_qSqldb);
        if (!qSqlQuery.exec(strdeleteTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
        strdeleteTable = "update sqlite_sequence set seq = 0 where name = 'userdata'";
        if (!qSqlQuery.exec(strdeleteTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
        strdeleteTable = "delete from sqlite_sequence where name = 'userdata'";
        if (!qSqlQuery.exec(strdeleteTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
        strdeleteTable = "delete from sqlite_sequence";
        if (!qSqlQuery.exec(strdeleteTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }
    return true;
}

bool CUserInfoDB::GetAllDataUserData(QVector<QStringList> &qAllDataVector)
{
    if(m_qSqldb.isOpen())
    {
        QString strSelect = QString("SELECT * FROM userdata");
        QSqlQuery qSqlQuery(strSelect,m_qSqldb);//
        int iAllDBIndexCount = m_iDBIndexCount + 1;
        while(qSqlQuery.next())
        {
            QStringList strLineDataList;
            for(int i = 0; i != iAllDBIndexCount; ++i)
            {
                strLineDataList.push_back(qSqlQuery.value(i).toString());
            }
            qAllDataVector.push_back(strLineDataList);
        }
        return true;
    }
    return false;
}

int CUserInfoDB::FindUserID(QString strUserName)
{
    int iId = -1;
    if(strUserName.isEmpty())
    {
        return iId;
    }

    if(m_qSqldb.isOpen())
    {
        QString strSelect = QString("SELECT * FROM userdata WHERE UserName = '")
                + strUserName + "'";
        QSqlQuery qSqlQuery(strSelect,m_qSqldb);//
        while(qSqlQuery.next())
        {
            iId = qSqlQuery.value(0).toInt();
            return iId;
        }
    }
    return iId;
}

bool CUserInfoDB::FindUserPassWord(QString strUserName, QString &strPassWord)
{
    strPassWord = "";
    if(strUserName.isEmpty())
    {
        return false;
    }

    if(m_qSqldb.isOpen())
    {
        QString strSelect = QString("SELECT * FROM userdata WHERE UserName = '")
                + strUserName + "'";
        QSqlQuery qSqlQuery(strSelect,m_qSqldb);//
        if(qSqlQuery.next())
        {
            strPassWord = qSqlQuery.value(2).toString();
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

