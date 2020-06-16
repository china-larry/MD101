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
#include "CLabelDateWidget.h"
#include <QBoxLayout>
#include <QEvent>
#include <QDebug>

QBaseQDateEdit::QBaseQDateEdit(QWidget *parent)
{

}

void QBaseQDateEdit::mousePressEvent(QMouseEvent *event)
{

    //event->ignore();
    QDateEdit::mousePressEvent(event);
}

CLabelDateWidget::CLabelDateWidget(QWidget *parent)
    : QWidget(parent),
      m_qDate(QDate::currentDate())
{
    m_pLabel = new QLabel(this);
    m_pDateEdit = new CDayLineEdit(this);
    _InitLayout();
}

CLabelDateWidget::CLabelDateWidget(QString strLabel, QDate qDate, QWidget *parent)
    : QWidget(parent),
      m_qDate(qDate)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pDateEdit = new CDayLineEdit(qDate.toString("yyyy-MM-dd"),this);

    _InitLayout();
}

QDate CLabelDateWidget::GetDate()
{
    m_qDate = QDate::fromString(m_pDateEdit->text(), "yyyy-MM-dd");
    return m_qDate;
}

void CLabelDateWidget::SetDate(QDate qDate)
{  
    m_qDate = qDate;
    m_pDateEdit->setText(m_qDate.toString("yyyy-MM-dd"));
}
void CLabelDateWidget::SetDateObject(QString strObjectName)
{
    m_pDateEdit->setObjectName(strObjectName);
}
//void CLabelDateWidget::keyPressEvent(QKeyEvent *)
//{
//    BeepManager::GetInstance()->lound(1);
//}

//void CLabelDateWidget::DateChanged(QDate qDate)
//{
//    BeepManager::GetInstance()->lound(1);
//}

void CLabelDateWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pLabel);
    pLayout->addSpacing(10);
    pLayout->addWidget(m_pDateEdit);
    this->setLayout(pLayout);
}

//bool CLabelDateWidget::eventFilter(QObject *watched, QEvent *event)
//{
//     if (watched == m_pDateEdit)         //首先判断控件(这里指 lineEdit1)
//     {
//          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
//          {

//          }
//          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
//          {
//                if(m_pDateEdit->date().year() == 0)
//                {
//                    m_pDateEdit->setDate(QDate::currentDate());
//                }
//              //qDebug() << m_pDateEdit->date().year();
//          }
//     }

//    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
//}


CVLabelDateWidget::CVLabelDateWidget(QWidget *parent)
    : QWidget(parent),
      m_qDate(QDate::currentDate())
{
    m_pLabel = new QLabel(this);
    m_pDateEdit = new CDayLineEdit(this);

    _InitLayout();
}

CVLabelDateWidget::CVLabelDateWidget(QString strLabel, QDate qDate, QWidget *parent)
    : QWidget(parent),
      m_qDate(qDate)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pDateEdit = new CDayLineEdit(qDate.toString("yyyy-MM-dd"),this);

    _InitLayout();
}

//void CVLabelDateWidget::DateChanged(QDate)
//{
//    BeepManager::GetInstance()->lound(1);
//}

QDate CVLabelDateWidget::GetDate()
{
    m_qDate = QDate::fromString(m_pDateEdit->text(), "yyyy-MM-dd");
    return m_qDate;
}

void CVLabelDateWidget::SetDate(QDate qDate)
{
    m_qDate = qDate;
    m_pDateEdit->setText(m_qDate.toString("yyyy-MM-dd"));
}

void CVLabelDateWidget::SetDateObject(QString strObjectName)
{
    m_pDateEdit->setObjectName(strObjectName);
}

//void CVLabelDateWidget::keyPressEvent(QKeyEvent *)
//{
//    BeepManager::GetInstance()->lound(1);
//}

void CVLabelDateWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pLabel);
    pLayout->addWidget(m_pDateEdit);
    this->setLayout(pLayout);
}

//bool CVLabelDateWidget::eventFilter(QObject *watched, QEvent *event)
//{
//     if (watched == m_pDateEdit)         //首先判断控件(这里指 lineEdit1)
//     {
//          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
//          {

//          }
//          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
//          {
//                if(m_pDateEdit->date().year() == 0)
//                {
//                    m_pDateEdit->setDate(QDate::currentDate());
//                }
//              //qDebug() << m_pDateEdit->date().year();
//          }
//     }

//    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
//}



