#include "CLogDB.h"
CLogDB* CLogDB::m_pInstance = new CLogDB();
CLogDB::CLogDB(QObject *parent) : QObject(parent)
{

}

CLogDB::~CLogDB()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CLogDB *CLogDB::GetInstance()
{
    return m_pInstance;
}

void CLogDB::InitDataBase()
{

}
