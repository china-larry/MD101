#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "MDWidget/CPageStatusWidget.h"
#include "MDWidget/CPageTitleWidget.h"
#include "LoginPage/CLoginInWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void SlotShwoMenu();
    // 标题栏
   void SlotReceiveLogin(int iUserPower, QString strUserName);// 登陆界面跳转
private slots:
    void _SlotMenuChanged(QModelIndex index);
private:
    void _InitWidget();
    void _InitLayout();
private:
    Ui::MainWindow *ui;
    QVBoxLayout *m_pMainLayout;
    QWidget *m_pCentralWidget;// 布局
    //
    CLoginInWidget *m_pCLoginInWidget;

    // 多标签 切换控件
    QStackedWidget *m_pStackedWidget;

    CPageTitleWidget *m_pCPageTitleWidget;
    CPageStatusWidget *m_pCPageStatusWidget;

    int m_kiTitleHeight;// 标题栏高度
    int m_kiStatusBarHeight;
    QRect m_iWidgetRect;

    QListView *m_pQListView;
    bool m_bShowMenu;
    //
    bool m_bLeftButtonCheck;
    QPoint m_qPressPoint;
    QPoint m_qMovePoint;


};
#endif // MAINWINDOW_H
