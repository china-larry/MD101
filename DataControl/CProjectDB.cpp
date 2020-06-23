#include "CProjectDB.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "PublicConfig.h"
#include "PublicFunction.h"

CProjectDB* CProjectDB::m_pInstance = new CProjectDB();
CProjectDB::CProjectDB(QObject *parent) : QObject(parent)
{

}

CProjectDB::~CProjectDB()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CProjectDB *CProjectDB::GetInstance()
{

    return m_pInstance;
}

void CProjectDB::InitDataBase()
{
    _InitCardInfoDB();
    _InitSampleInfoDB();
    _InitPersonInfoDB();
}

void CProjectDB::_InitCardInfoDB()
{
    m_qSqldb = ConnectDataBase(gc_strProjectDB, gc_strProjectDBConnect);
    if(m_qSqldb.isOpen() == false)
    {
        m_qSqldb.open();
    }
    if(m_qSqldb.isOpen())
    {
        QString strCreateTable  = "CREATE TABLE card ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "CardID VARCHAR,"
                                  "ProjectName VARCHAR,"
                                  "CardVersion VARCHAR,"
                                  "ExpirationDate VARCHAR,"
                                  "ProductLot VARCHAR,"
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

void CProjectDB::_InitSampleInfoDB()
{
    m_qSqldb = ConnectDataBase(gc_strProjectDB, gc_strProjectDBConnect);
    if(m_qSqldb.isOpen() == false)
    {
        m_qSqldb.open();
    }
    if(m_qSqldb.isOpen())
    {
        QString strCreateTable  = "CREATE TABLE sample ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "SampleID VARCHAR,"
                                  "SampleType VARCHAR,"
                                  "SerialNo VARCHAR,"
                                  "SampleNumber VARCHAR,"
                                  "ApplicationTime VARCHAR,"
                                  "SourceFrom VARCHAR,"
                                  "CardID VARCHAR,"
                                  "PatientID VARCHAR,"
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

void CProjectDB::_InitPersonInfoDB()
{
    m_qSqldb = ConnectDataBase(gc_strProjectDB, gc_strProjectDBConnect);
    if(m_qSqldb.isOpen() == false)
    {
        m_qSqldb.open();
    }
    if(m_qSqldb.isOpen())
    {
        QString strCreateTable  = "CREATE TABLE patient ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "PatientID VARCHAR,"
                                  "Name VARCHAR,"
                                  "Gender VARCHAR,"
                                  "Age VARCHAR,"
                                  "Department VARCHAR," // 科室
                                  "AdmissionNumber VARCHAR," // 住院号
                                  "BedNumber VARCHAR," // 床号
                                  "ReferralDoctor VARCHAR,"// 送检医生
                                  "InspctorName VARCHAR," // 检验医生
                                  "ReviewersName VARCHAR," // 复核者
                                  "SamplingTime VARCHAR," // 采样时间
                                  "SubmissionTime VARCHAR," // 送检时间
                                  "Remarks VARCHAR)"; //

       // qDebug() << "cread history " << strCreateTable;
        // 创建
        QSqlQuery qSqlQuery(m_qSqldb);
        if (!qSqlQuery.exec(strCreateTable))
        {
            qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }
}
