#include "CTestPage.h"
#include <QBoxLayout>
#include "PublicFunction.h"

CTestPage::CTestPage(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
   // SetWidgetBackColor(this, QColor(0xF1, 0xF6, 0xFB));


    _InitWidget();
    _InitLayout();
}

void CTestPage::_InitWidget()
{
    m_pCShowImageWidget = new CShowImageWidget(this);
    m_pCShowImageWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCShowImageWidget->setObjectName("m_pCShowImageWidget");

    m_pCCardInfoWidget = new CCardInfoWidget(this);
    m_pCCardInfoWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCCardInfoWidget->setObjectName("m_pCCardInfoWidget");
    m_pCCardInfoWidget->hide();
    //
    m_pCSampleInfoWidget = new CSampleInfoWidget(this);
    m_pCSampleInfoWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCSampleInfoWidget->setObjectName("m_pCSampleInfoWidget");
//    m_pCSampleInfoWidget->hide();

    m_pNextStepButton = new QPushButton(tr("下一步"), this);
    m_pNextStepButton->setFixedSize(158, 50);
    m_pNextStepButton->setObjectName("m_pNextStepButton");
    m_pStopTestButton = new QPushButton(tr("取消测试"), this);
    m_pStopTestButton->setFixedSize(158, 50);
    m_pStopTestButton->setObjectName("m_pStopTestButton");
}

void CTestPage::_InitLayout()
{
    //
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addWidget(m_pStopTestButton);
    pButtonLayout->addWidget(m_pNextStepButton);
    //
    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->addSpacing(5);
    pRightLayout->addWidget(m_pCSampleInfoWidget);
    pRightLayout->addStretch(1);
    pRightLayout->addLayout(pButtonLayout);
    pRightLayout->addSpacing(15);
    //
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(m_pCShowImageWidget);
    pLayout->addLayout(pRightLayout);

    this->setLayout(pLayout);

}
