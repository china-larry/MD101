#include "CPrintPreviewTitleWidget.h"
#include <QBoxLayout>
#include "PublicFunction.h"
CPrintPreviewTitleWidget::CPrintPreviewTitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1030, 50);
    _InitWidget();
    _InitLayout();
    //
    this->setAutoFillBackground(true);  //自动填充背景
    //SetWidgetBackImage(this, ":/image/ico/title/titlebackimage.png");
    SetWidgetBackColor(this, QColor(0x00, 0x68, 0xB8));
}

void CPrintPreviewTitleWidget::SetUserName(QString strUserName)
{
     m_pOperatorIDLineEdit->setText("Operator ID: " + strUserName);
}

void CPrintPreviewTitleWidget::_InitWidget()
{
    // logo
    m_pLogoLabel = new QLabel(this);
    m_pLogoLabel->setFixedSize(172, 50);
    if(gk_iVersionConfig == ADMIN_VERSION)
    {
        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/PIS_logo.png"));
    }
    else if(gk_iVersionConfig == OTHER_VERSION)
    {
        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/MD_logo.png"));
    }
    else
    {
        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/WONDFO_logo.png"));
    }
    // Operator ID
    m_pOperatorIDLineEdit = new  CVLineEdit("Operator ID:", this);
    m_pOperatorIDLineEdit->setFixedSize(182, 30);
    m_pOperatorIDLineEdit->setEnabled(false);
    //
    m_pMinWindowButton = new QPushButton(this);
    m_pMinWindowButton->setFixedSize(60, 50);
    SetButtonBackImage(m_pMinWindowButton, ":/image/ico/title/mini.jpg");
    connect(m_pMinWindowButton, SIGNAL(clicked(bool)), this, SIGNAL(SignalMinWindow()));
    m_pCloseWindowButton = new QPushButton(this);
    m_pCloseWindowButton->setFixedSize(60, 50);
    SetButtonBackImage(m_pCloseWindowButton, ":/image/ico/title/close02.jpg");
    connect(m_pCloseWindowButton, SIGNAL(clicked(bool)), this, SIGNAL(SignalCloseWindow()));
}

void CPrintPreviewTitleWidget::_InitLayout()
{
    LoadQss(this, ":/qss/DetectorPage/MainTitle.qss");
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLogoLabel);
    pLayout->addSpacing(2);
    pLayout->addWidget(m_pOperatorIDLineEdit);

    pLayout->addStretch(88);
    pLayout->addWidget(m_pMinWindowButton);
    pLayout->addWidget(m_pCloseWindowButton);
    pLayout->addSpacing(6);

    this->setLayout(pLayout);
}
