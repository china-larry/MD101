#include "CCardInfoWidget.h"
#include <QBoxLayout>
#include "PublicFunction.h"
CCardInfoWidget::CCardInfoWidget(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
    this->setFixedSize(810, 525);
    _InitWidget();
    _InitLayout();
}

void CCardInfoWidget::_InitWidget()
{
    m_pCLabelMarkWidget = new CLabelMarkWidget(tr("卡盒信息"), this);
    m_pProjectNameWidget = new CHLabelLineEditWidget(tr("项目名称"), tr(""), this);

    m_pCardIDWidget = new CHLabelLineEditWidget(tr("试剂盒ID"), tr(""), this);
    m_pCardIDLabel = new QLabel("*", this);
    m_pProjectLotWidget = new CHLabelLineEditWidget(tr("产品批号"), tr(""), this);
    m_pCardVersionWidget = new CHLabelLineEditWidget(tr("测试版本"), tr(""), this);
}

void CCardInfoWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(20);
    pLayout->addSpacing(15);
    pLayout->addWidget(m_pCLabelMarkWidget, 0, Qt::AlignLeft);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pProjectNameWidget, 0, Qt::AlignCenter);
    QHBoxLayout *pIDLayout = new  QHBoxLayout;
    pIDLayout->addSpacing(225);
    pIDLayout->addWidget(m_pCardIDWidget);
    pIDLayout->addSpacing(10);
    pIDLayout->addWidget(m_pCardIDLabel);
    pIDLayout->addStretch(1);
    pLayout->addLayout(pIDLayout);
    pLayout->addWidget(m_pProjectLotWidget, 0, Qt::AlignCenter);
    pLayout->addWidget(m_pCardVersionWidget, 0, Qt::AlignCenter);
    pLayout->addSpacing(120);

    this->setLayout(pLayout);
}
