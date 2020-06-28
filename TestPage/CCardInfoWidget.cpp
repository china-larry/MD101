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

SCardInfoStruct CCardInfoWidget::GetCardInfo()
{
    SCardInfoStruct sSCardInfoStruct;
    sSCardInfoStruct.strCardID = m_pCardIDWidget->GetLineText();
    sSCardInfoStruct.strProjectName = m_pProjectNameWidget->GetLineText();
    sSCardInfoStruct.strProjectLot = m_pProjectLotWidget->GetLineText();
    sSCardInfoStruct.strExpirationDate = m_pExpirationDateWidget->GetLineText();
    sSCardInfoStruct.strCardVersion = m_pCardVersionWidget->GetLineText();

    return sSCardInfoStruct;
}

void CCardInfoWidget::_InitWidget()
{
    m_pCLabelMarkWidget = new CLabelMarkWidget(tr("卡盒信息"), this);
    m_pProjectNameWidget = new CHLabelLineEditWidget(tr("项目名称"), tr(""), this);

    m_pCardIDWidget = new CHLabelLineEditWidget(tr("试剂盒ID"), tr(""), this);
    m_pCardIDLabel = new QLabel("*", this);
    m_pCardIDLabel->setObjectName("m_pCardIDLabel");
    m_pProjectLotWidget = new CHLabelLineEditWidget(tr("产品批号"), tr(""), this);
    m_pExpirationDateWidget = new CHLabelLineEditWidget(tr("有效日期"), tr(""), this);
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
    pIDLayout->setMargin(0);
    pIDLayout->setSpacing(0);
    pIDLayout->addSpacing(230);
    pIDLayout->addWidget(m_pCardIDWidget);
    pIDLayout->addSpacing(2);
    pIDLayout->addWidget(m_pCardIDLabel);
    pIDLayout->addStretch(1);
    pLayout->addLayout(pIDLayout);
    pLayout->addWidget(m_pProjectLotWidget, 0, Qt::AlignCenter);
    pLayout->addWidget(m_pExpirationDateWidget, 0, Qt::AlignCenter);
    pLayout->addWidget(m_pCardVersionWidget, 0, Qt::AlignCenter);
    pLayout->addSpacing(80);

    this->setLayout(pLayout);
}
