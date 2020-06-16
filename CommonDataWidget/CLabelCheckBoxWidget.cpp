/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和CheckBox
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLabelCheckBoxWidget.h"
#include <QBoxLayout>
#include <QDebug>
CLabelCheckBoxWidget::CLabelCheckBoxWidget(QWidget *parent) : QWidget(parent)
{

}

CLabelCheckBoxWidget::CLabelCheckBoxWidget(QString strLabel, QString strBoxName, bool bCheck, QWidget *parent)
    : QWidget(parent),
      m_bCheckFlag(bCheck)
{
   m_pLabel = new QLabel(strLabel, this);
   m_pCheckBox = new QCheckBox(strBoxName, this);
   m_pCheckBox->setChecked(bCheck);
   connect(m_pCheckBox, SIGNAL(clicked(bool)), this, SLOT(_SlotChangeCheck(bool)));

   _InitLayout();
}

void CLabelCheckBoxWidget::_SlotChangeCheck(bool bCheck)
{
    m_bCheckFlag = bCheck;
//    qDebug() << "chekc fla" << m_bCheckFlag;
}

bool CLabelCheckBoxWidget::GetCheckFlag()
{
    return m_bCheckFlag;
}

void CLabelCheckBoxWidget::SetCheckFlag(bool bFlag)
{
    m_bCheckFlag = bFlag;
    m_pCheckBox->setChecked(bFlag);
}

void CLabelCheckBoxWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addSpacing(50);
    pLayout->addWidget(m_pCheckBox);
    this->setLayout(pLayout);
}
