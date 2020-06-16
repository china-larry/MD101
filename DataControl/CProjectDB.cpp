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

}

void CProjectDB::_InitCardInfoDB()
{

}

void CProjectDB::_InitSampleInfoDB()
{

}

void CProjectDB::_InitPersonInfoDB()
{

}
