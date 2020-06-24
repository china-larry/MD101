#ifndef CDAYTIMEDIALOG_H
#define CDAYTIMEDIALOG_H
#include <QCalendarWidget>
#include <QLineEdit>
#include <QDialog>

#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "PublicFunction.h"

// 基类，年 + 数字 - 四个控件
class CTimeObject : public QWidget
{
    Q_OBJECT
public:
    explicit CTimeObject(QWidget *parent = nullptr);
    explicit CTimeObject(QString strName, QSize qSize, QWidget *parent = nullptr);

signals:
public slots:
    void _SlotAdd();
    void _SlotSub();
public:
    void SetValue(int iValue);
    int GetValue();
private:
    void _InitWidget();
    void _InitLayout();
private:
    QLabel *m_pNameLabel;
    QPushButton *m_pAddButton;//  加
    QLineEdit *m_pValueLineEdit;
    QPushButton *m_pSubButton;// 减

    QString m_strName;
    int m_iValue;
    QSize m_qSize;// 控件大小
};
class CDayDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CDayDialog(QWidget *parent = nullptr);
    void showEvent(QShowEvent *pEvent);
signals:


public slots:
    void SlotOk();
    void SlotCancel();
public:
    //获取类对象
    static CDayDialog* GetInstance();
    //类对象
    static CDayDialog* m_pInstance;
    //
    void SetDate(QString strDate);
    QString GetDate();
private:
    void _InitWidget();
    void _InitLayout();
private:
    CTimeObject *m_pYearWidget;//  年
    CTimeObject *m_pMonthWidget;// 月
    CTimeObject *m_pDayWidget;// 日

    QPushButton *m_pOKButton;// 确认
    QPushButton *m_pCancelButton;// 确认
};
class CDayTimeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CDayTimeDialog(QWidget *parent = nullptr);
    void showEvent(QShowEvent *pEvent);
signals:


public slots:
    void SlotOk();
    void SlotCancel();
public:
    //获取类对象
    static CDayTimeDialog* GetInstance();
    //类对象
    static CDayTimeDialog* m_pInstance;
    //
    void SetDateTime(QString strDate);
    QString GetDateTime();
private:
    void _InitWidget();
    void _InitLayout();
private:
    CTimeObject *m_pYearWidget;//  年
    CTimeObject *m_pMonthWidget;// 月
    CTimeObject *m_pDayWidget;// 日
    CTimeObject *m_pTimeWidget;// 时
    CTimeObject *m_pMinWidget;// 分
    CTimeObject *m_pSecWidget;// 秒

    QPushButton *m_pOKButton;// 确认
    QPushButton *m_pCancelButton;// 确认
};

class CDayLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CDayLineEdit(QWidget *parent = 0);
    explicit CDayLineEdit(QString str, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
signals:

public slots:


private:
    CDayDialog *m_pCDayDialog;
};

#endif // CDAYTIMEDIALOG_H
