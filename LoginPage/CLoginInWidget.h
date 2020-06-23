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
#ifndef CLOGININWIDGET_H
#define CLOGININWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include "CUserNameCommonBox.h"
class CLoginInWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLoginInWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void _SlotCheckMinButton();
    void _SlotCheckCloseButton();
    void _SlotCheckLoginButton();
signals:
    void SigShowMainWindow(int iUserPower, QString strUserName);// 显示主窗口
public slots:
private slots:
    void _SlotPasswordChange();
public:
    int GetUserPower();// 获取用户权限，0为普通，1为管理，2为维护人员
private:
    void _InitWidget();
    void _InitLayout();
    int _CheckUserPower();// 用户名和权限验证
    void _SaveUserName();
    void _ReadUserName();
private:
//    QLabel *m_pLoginLabel;
    // user
    CUserNameCommonBox *m_pUserNameWidget;
    // password
    CPasswordWidget *m_pPasswordWidget;
    QPushButton *m_pPasswordHidButton;

    //
    QPushButton *m_pLoginButton;
    // 用户数据库
    QString m_strDatabaseName;
    int m_iUserPower; // 用户权限，0为普通，1为管理，2为维护人员
    QString m_strAdminUserName;
    QString m_strAdminPassWord;
    QString m_strModifyUserName;
    QString m_strModifyPassWord;
    QString m_strUserName;
    //
    bool m_bShowWindows;

    //
    bool m_bLeftButtonCheck;
    QPoint m_qPressPoint;
    QPoint m_qMovePoint;

};

#endif // CLOGININWIDGET_H
