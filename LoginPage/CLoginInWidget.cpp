/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 登陆页面Widget，用户登陆操作
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLoginInWidget.h"
#include <QBoxLayout>
#include <QFont>
#include <QPixmap>
#include <QBitmap>
#include <QPalette>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QApplication>
#include <QtDebug>
#include "PublicFunction.h"
#include "DataControl/CUserInfoDB.h"
#include "CommonDataWidget/CMessageBox.h"
CLoginInWidget::CLoginInWidget(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(1280, 800);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    // 设置b背景图片
    SetWidgetBackImage(this, ":/image/ico/login/mdx.jpg");
    //
    LoadQss(this, ":/qss/LoginPage/LoginPage.qss");
    //
    _InitWidget();
    _InitLayout();
    // 数据库
    m_iUserPower = 2;//
    m_strAdminUserName = "admin";
    m_strAdminPassWord = "123";
    m_strModifyUserName = "super";
    m_strModifyPassWord = "123";
    // 焦点定位
    //m_pUserNameLineEdit->setFocus();
    m_pPasswordWidget->setFocus();
    //m_pLoginButton->setFocus();
    //
    m_bShowWindows = true;
    _ReadUserName();
}

void CLoginInWidget::_SlotCheckMinButton()
{
    this->showMinimized();
}

void CLoginInWidget::_SlotCheckCloseButton()
{
    if(ShowQuestion(NULL, "Warning", "Are you sure to quit?",
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        this->close();
    }
}


void CLoginInWidget::_SlotCheckLoginButton()
{
    // 检查Username及权限
    qDebug() << __FUNCTION__ << __LINE__;

    m_iUserPower = 2;//_CheckUserPower();
//    qDebug() << "user power" << m_iUserPower;
    if(m_iUserPower >= 0 && m_bShowWindows)
    {//
        _SaveUserName();
        m_bShowWindows = false;
        emit SigShowMainWindow(m_iUserPower,m_pUserNameWidget->GetCurrentSelectText());
//        qDebug() << "SigShowMainWindow";
        this->hide();


    }
    qDebug() << __FUNCTION__ << __LINE__;
}

void CLoginInWidget::_SlotPasswordChange()
{
    //this->setFocusPolicy(Qt::StrongFocus);
}

int CLoginInWidget::GetUserPower()
{
    return m_iUserPower;
}

/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CLoginInWidget::_InitWidget()
{
    //获得所有用户名称
    QVector<QStringList> strAllUserDataVector;
    CUserInfoDB::GetInstance()->GetAllDataUserData(strAllUserDataVector);
    QStringList strAllUserNameList;
    QStringList strDataListTmp;
    for(int i = 0; i < strAllUserDataVector.count(); ++i)
    {
        strDataListTmp = strAllUserDataVector[i];
        if(strDataListTmp.count() > 2)
        {
            strAllUserNameList.push_back(strDataListTmp[1]);
        }
    }
    m_pUserNameWidget = new CUserNameCommonBox(strAllUserNameList, this);
    // pass
   // m_pPasswordLabel->setObjectName("m_pUserNameLabel");
    m_pPasswordWidget = new CPasswordWidget(this);
//    m_pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    m_pPasswordWidget->SetFixSize(390, 60);
  //  connect(m_pPasswordLineEdit, &QLineEdit::textChanged, this, &CLoginInWidget::_SlotPasswordChange);

    m_pLoginButton = new QPushButton(tr("登 录"), this);
    m_pLoginButton->setObjectName("m_pLoginButton");

    connect(m_pLoginButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckLoginButton()));
}
/**
  * @brief 布局
  * @param
  * @return
  */
void CLoginInWidget::_InitLayout()
{
    // username
    QHBoxLayout *pUserNameLableHLayout = new QHBoxLayout;
    pUserNameLableHLayout->addStretch(1);
    pUserNameLableHLayout->addWidget(m_pUserNameWidget);
    pUserNameLableHLayout->addStretch(1);
    //
    // password
    //
    QHBoxLayout *pPasswordLineHLayout = new QHBoxLayout;
    pPasswordLineHLayout->addStretch(1);
    pPasswordLineHLayout->addWidget(m_pPasswordWidget);
    pPasswordLineHLayout->addStretch(1);
    //
    //
    QHBoxLayout *pLoadInHLayout = new QHBoxLayout;
    pLoadInHLayout->addStretch(1);
    pLoadInHLayout->addWidget(m_pLoginButton);
    pLoadInHLayout->addStretch(1);
    //

    QVBoxLayout *pVLayout = new QVBoxLayout;
    pVLayout->setMargin(0);
    pVLayout->addSpacing(282);
    pVLayout->addLayout(pUserNameLableHLayout);
    pVLayout->addSpacing(14);
    pVLayout->addLayout(pPasswordLineHLayout);
    pVLayout->addSpacing(55);
    pVLayout->addLayout(pLoadInHLayout);
    pVLayout->addStretch(1);
    //
    this->setLayout(pVLayout);
}
/**
  * @brief 验证用户和权限
  * @param
  * @return -1：无效用户，0：普通用户，1：管理员，2：维护人员
  */
int CLoginInWidget::_CheckUserPower()
{
    qDebug() << __FUNCTION__ << __LINE__;
    QString strUserName = m_pUserNameWidget->GetCurrentSelectText();
    QString strPassWord = m_pPasswordWidget->GetCurrentText();
    QString strDataPassWord = "";// 数据库中存储Password
    if(strUserName.isEmpty())
    {
        ShowCritical(NULL, tr("Error!"),
                         tr("Please Input Username!"));
        return -1;
    }

    qDebug() << __FUNCTION__ << __LINE__;
    if(strUserName == m_strAdminUserName)
    {
        if(strPassWord == m_strAdminPassWord)
        {
            qDebug() << "admin user";
            return 1;
        }
        else
        {
            // PasswordError
            ShowCritical(NULL, tr("Error!"),
                             tr("PasswordError!"));
            return -1;
        }
    }
    else if(strUserName == m_strModifyUserName)
    {
        if(strPassWord == m_strModifyPassWord)
        {
            qDebug() << "modify user";
            return 2;
        }
        else
        {
            // PasswordError
            ShowCritical(NULL, tr("Error!"),
                             tr("PasswordError!"));
            return -1;
        }

    }

    // 数据库查询
    bool bFind = CUserInfoDB::GetInstance()->FindUserPassWord(strUserName, strDataPassWord);
    if(bFind)
    {
        if(strPassWord == strDataPassWord)
        {
            return 0;
        }
        else
        {
            ShowCritical(NULL, tr("Error!"),
                             tr("PasswordError!"));
            return -1;
        }

    }
    else
    {
        ShowCritical(NULL, tr("Error!"),
                         tr("Username Not exist!"));
        return -1;
    }

    return -1;
}

void CLoginInWidget::_SaveUserName()
{
    QString strUserName = m_pUserNameWidget->GetCurrentSelectText();
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
    QMap<QString,QVariant> strSaveMotorDataMap;
    strSaveMotorDataMap.insert("user_name", strUserName);

    bool bMotor = WriteJsonMap(strFileName, "Login", strSaveMotorDataMap);
    if(bMotor)
    {
        qDebug() << "save ok" ;
    }
    else
    {
        qDebug() << "save fasle" ;
    }
    qDebug() << "save user" << strUserName;
}

void CLoginInWidget::_ReadUserName()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";

    QMap<QString,QVariant> strOperDataMap;
    if(ReadJsonMap(strFileName, "Login", &strOperDataMap))
    {
        QString strUserName = strOperDataMap.value("user_name").toString();
        qDebug() << "reda user name" << strUserName;
        if(!strUserName.isEmpty())
        {
            m_pUserNameWidget->SetCurrentText(strUserName);
        }
    }
    else
    {
        //ShowCritical(NULL, tr("Error"), tr("Critical Data lost"));
        //qDebug() << "reda MotorLight config error";
    }
}
