#include "CLabelLabelWidget.h"
#include <QBoxLayout>
CLabelLabelWidget::CLabelLabelWidget(QWidget *parent) : QWidget(parent)
{

}

CLabelLabelWidget::CLabelLabelWidget(QString strLabelName, QString strShowValue, QWidget *parent)
: QWidget(parent)
, m_strLabel(strLabelName)
, m_strValue(strShowValue)
{
    _InitWidget();
    _InitLayout();
}

void CLabelLabelWidget::SetValue(QString strValue, bool bColor)
{
    m_strValue = strValue;
    m_pShowValue->setText(m_strValue);
    if(bColor)
    {

    }
    else
    {

    }
}

void CLabelLabelWidget::_InitWidget()
{
    m_pLabel = new QLabel(m_strLabel, this);
    m_pShowValue = new QLabel(m_strValue, this);
}

void CLabelLabelWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addWidget(m_pShowValue);
    this->setLayout(pLayout);
}
