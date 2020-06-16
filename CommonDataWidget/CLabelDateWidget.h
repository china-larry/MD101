/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和Date
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CLABELDATEWIDGET_H
#define CLABELDATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDateEdit>
#include <QCalendarWidget>
#include "CommonDataWidget/CDayTimeDialog.h"
class QBaseQDateEdit : public QDateEdit
{
    Q_OBJECT

public:
    explicit QBaseQDateEdit(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

};

class CLabelDateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelDateWidget(QWidget *parent = 0);
    explicit CLabelDateWidget(QString strLabel, QDate qDate, QWidget *parent = 0);

signals:

public slots:

//    void DateChanged(QDate);
public:
    QDate GetDate();
    void SetDate(QDate qDate);
    void SetDateObject(QString strObjectName);

protected:
//    void keyPressEvent(QKeyEvent *);
//    bool eventFilter(QObject *,QEvent *);
private:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    CDayLineEdit *m_pDateEdit;
    QDate m_qDate;
};


class CVLabelDateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVLabelDateWidget(QWidget *parent = 0);
    explicit CVLabelDateWidget(QString strLabel, QDate qDate, QWidget *parent = 0);

signals:

public slots:

//    void DateChanged(QDate);
public:
    QDate GetDate();
    void SetDate(QDate qDate);
    void SetDateObject(QString strObjectName);

protected:
//    void keyPressEvent(QKeyEvent *);
//    bool eventFilter(QObject *,QEvent *);
private:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    CDayLineEdit *m_pDateEdit;
    QDate m_qDate;
};

#endif // CLABELDATEWIDGET_H
