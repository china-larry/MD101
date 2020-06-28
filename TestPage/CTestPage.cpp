#include "CTestPage.h"
#include <QBoxLayout>
#include "PublicFunction.h"

CTestPage::CTestPage(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
   // SetWidgetBackColor(this, QColor(0xF1, 0xF6, 0xFB));
    _InitWidget();
    _InitLayout();
    m_iCurrentStepIndex = 0;
}

void CTestPage::showEvent(QShowEvent *pEvent)
{
    m_iCurrentStepIndex = 0;
    _UpdateWidget();
}

void CTestPage::_SlotPreStep()
{
    --m_iCurrentStepIndex;
    _UpdateWidget();
}

void CTestPage::_SlotNextStep()
{
    ++m_iCurrentStepIndex;
    _UpdateWidget();

}

void CTestPage::_SlotStopTest()
{

}

void CTestPage::_SlotOpenDoor()
{

}

void CTestPage::_SlotCloseDoor()
{

}

void CTestPage::_SlotStartTest()
{

}

void CTestPage::_InitWidget()
{
    m_pCShowImageWidget = new CShowImageWidget(this);
    m_pCShowImageWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCShowImageWidget->setObjectName("m_pCShowImageWidget");

    m_pCCardInfoWidget = new CCardInfoWidget(this);
    m_pCCardInfoWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCCardInfoWidget->setObjectName("m_pCCardInfoWidget");
//    m_pCCardInfoWidget->hide();
    //
    m_pCSampleInfoWidget = new CSampleInfoWidget(this);
    m_pCSampleInfoWidget->setAttribute(Qt::WA_StyledBackground,true);
    m_pCSampleInfoWidget->setObjectName("m_pCSampleInfoWidget");
    m_pCSampleInfoWidget->hide();

    //
    m_pPreStepButton = new QPushButton(tr("    上一步"), this);
    m_pPreStepButton->setFixedSize(158, 50);
    m_pPreStepButton->setObjectName("m_pPreStepButton");
    connect(m_pPreStepButton, &QPushButton::clicked,
            this, &CTestPage::_SlotPreStep);
    m_pPreStepButton->hide();
    //
    m_pNextStepButton = new QPushButton(tr("    下一步"), this);
    m_pNextStepButton->setFixedSize(158, 50);
    m_pNextStepButton->setObjectName("m_pNextStepButton");
    connect(m_pNextStepButton, &QPushButton::clicked,
            this, &CTestPage::_SlotNextStep);
    m_pStopTestButton = new QPushButton(tr("   取消测试"), this);
    m_pStopTestButton->setFixedSize(158, 50);
    m_pStopTestButton->setObjectName("m_pStopTestButton");
    connect(m_pStopTestButton, &QPushButton::clicked,
            this, &CTestPage::_SlotStopTest);
    //
    m_pOpenDoorButton = new QPushButton(tr("    打开仓门"), this);
    m_pOpenDoorButton->setFixedSize(158, 50);
    m_pOpenDoorButton->setObjectName("m_pOpenDoorButton");
    connect(m_pOpenDoorButton, &QPushButton::clicked,
            this, &CTestPage::_SlotOpenDoor);
    m_pOpenDoorButton->hide();
    //
    m_pCloseDoorButton = new QPushButton(tr("    关闭仓门"), this);
    m_pCloseDoorButton->setFixedSize(158, 50);
    m_pCloseDoorButton->setObjectName("m_pCloseDoorButton");
    connect(m_pCloseDoorButton, &QPushButton::clicked,
            this, &CTestPage::_SlotCloseDoor);
    m_pCloseDoorButton->hide();
    //
    m_pStartTestButton = new QPushButton(tr("    开始测试"), this);
    m_pStartTestButton->setFixedSize(158, 50);
    m_pStartTestButton->setObjectName("m_pStartTestButton");
    connect(m_pStartTestButton, &QPushButton::clicked,
            this, &CTestPage::_SlotStartTest);
    m_pStartTestButton->hide();
}

void CTestPage::_InitLayout()
{
    //
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addWidget(m_pPreStepButton);
    pButtonLayout->addWidget(m_pStopTestButton);
    pButtonLayout->addWidget(m_pNextStepButton);
    pButtonLayout->addWidget(m_pOpenDoorButton);
    pButtonLayout->addWidget(m_pCloseDoorButton);
    pButtonLayout->addWidget(m_pStartTestButton);
    //
    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->addSpacing(5);
    pRightLayout->addWidget(m_pCCardInfoWidget);
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

void CTestPage::_UpdateWidget()
{
    m_pCShowImageWidget->SetCurrentShow(m_iCurrentStepIndex);
    switch (m_iCurrentStepIndex)
    {
    case CardINfo:
        m_pNextStepButton->show();
        m_pStopTestButton->show();
        m_pCCardInfoWidget->show();
        m_pCSampleInfoWidget->hide();
        m_pPreStepButton->hide();
        m_pOpenDoorButton->hide();
        m_pCloseDoorButton->hide();
        m_pStartTestButton->hide();
        break;
    case SampleInfo:
        m_pCCardInfoWidget->hide();
        m_pCSampleInfoWidget->show();
        m_pPreStepButton->show();
        break;
    case AddSample:

        break;
    case OutCardChip:
        m_pNextStepButton->show();
        m_pOpenDoorButton->hide();
        m_pCloseDoorButton->hide();
        m_pStartTestButton->hide();
        break;
    case StartTest:
        m_pNextStepButton->hide();
        m_pOpenDoorButton->show();
        m_pCloseDoorButton->show();
        m_pStartTestButton->show();
        break;
    default:
        break;
    }
}
