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
                                  "DonorFirstName VARCHAR,"
                                  "DonorLastName VARCHAR,"
                                  "TestTime VARCHAR,"
                                  "Age VARCHAR,"
                                  "DonorID VARCHAR,"
                                  "TestSite VARCHAR,"
                                  "Operator VARCHAR,"
                                  "PreEmployment VARCHAR,"
                                  "Random VARCHAR,"
                                  "Scheduled VARCHAR,"
                                  "PInitial VARCHAR,"
                                  "CourtHearing VARCHAR,"
                                  "PostAccident VARCHAR,"
                                  "Reasonable VARCHAR,"
                                  "FollowUp VARCHAR,"
                                  "OtherReason VARCHAR,"
                                  "Comments VARCHAR,"
                                  "TemperatureNormal VARCHAR,"
                                  "Gender VARCHAR,"
                                  "ProductDefinition VARCHAR,"
                                  "ExpirationDate VARCHAR,"
                                  "ProductLot VARCHAR,"
                                  "ProductID VARCHAR,"
                                  "ProgramsNumber INT,";
        for(int i = 0; i < m_iMaxTestResult; ++i)
        {
            strCreateTable += QString("ProgramName") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("Result") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("Cutoff") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("T") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("C") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("T_C") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("ImagePath") + QString::number(i) + QString(" VARCHAR,");
        }
        strCreateTable += "PrintImagePath VARCHAR)";

       // //-qDebug() << "cread history " << strCreateTable;

        // 创建
        QSqlQuery qSqlQuery(m_qSqldb);
        if (!qSqlQuery.exec(strCreateTable))
        {
            //-qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }
}
