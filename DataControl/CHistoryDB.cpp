#include "CHistoryDB.h"
#include <QDebug>
#include <QSqlError>
#include <QString>
#include "PublicConfig.h"
#include "PublicFunction.h"
#include "CommonDataWidget/CMessageBox.h"
CHistoryDB* CHistoryDB::m_pInstance = new CHistoryDB();
CHistoryDB::CHistoryDB(QObject *parent) : QObject(parent)
{
    m_iDatabaseColumnCount = 166;// 当前列数，包括ID
    m_iResultIndexCount = 7;
    m_iMaxTestResult = 20;
}

CHistoryDB::~CHistoryDB()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CHistoryDB *CHistoryDB::GetInstance()
{
    return m_pInstance;
}

void CHistoryDB::InitDataBase()
{
    m_qSqldb = ConnectDataBase(gc_strHistoryDB, gc_strHistoryDBConnect);
    if(m_qSqldb.isOpen() == false)
    {
        m_qSqldb.open();
    }
    if(m_qSqldb.isOpen())
    {
        QString strCreateTable  = "CREATE TABLE historydata ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "SampleID VARCHAR,"
                                  "ProjectName VARCHAR,"
                                  "TestTime VARCHAR,"
                                  "Result VARCHAR,"
                                  "Operator VARCHAR,"
                                  "Status VARCHAR,"
                                  "Remarks VARCHAR)";

       // qDebug() << "cread history " << strCreateTable;
        // 创建
        QSqlQuery qSqlQuery(m_qSqldb);
        if (!qSqlQuery.exec(strCreateTable))
        {
            qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }
}
