
#include "CPageTitleWidget.h"
#include <QPalette>
#include <QDebug>
#include <QLinearGradient>
#include "PublicFunction.h"

CPageTitleWidget::CPageTitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1280, 80);
    LoadQss(this, ":/qss/DetectorPage/MainTitle.qss");
    _InitWidget();
    _InitLayout();
    //
    this->setAutoFillBackground(true);  //自动填充背景
    QLinearGradient qLineGradient(132, 0, 1024, 0);	//控制渐变色的走向
                qLineGradient.setColorAt(0.0, 0x2C4A93);				//渐变的颜色1
                qLineGradient.setColorAt(0.3, 0x2C4A93);				//渐变的颜色1
                qLineGradient.setColorAt(1.0, 0x1776CA);				//渐变的颜色2

        SetWidgetBackLineColor(this, qLineGradient);
}

void CPageTitleWidget::SetUserName(QString strUserName)
{

}


/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CPageTitleWidget::_InitWidget()
{
    SetWidgetBackImage(this, ":/image/ico/title/header.png");

    m_pStatusButton = new QPushButton(tr("  状态"),this);
    m_pStatusButton->setFixedSize(170, 80);
    m_pStatusButton->setObjectName("m_pStatusButton");
    connect(m_pStatusButton, &QPushButton::clicked, this, &CPageTitleWidget::SignalStatusButton);
    m_pStatusButton->setFlat(true);
//    m_pStatusButton->setStyleSheet("background-color:transparent");

    m_pTestButton = new QPushButton(tr("  测试"),this);
    m_pTestButton->setFixedSize(170, 80);
    m_pTestButton->setObjectName("m_pTestButton");
    connect(m_pTestButton, &QPushButton::clicked, this, &CPageTitleWidget::SignalTestButton);
    m_pTestButton->setFlat(true);
//    m_pTestButton->setStyleSheet("background-color:transparent");

    m_pHistoryButton = new QPushButton(tr("  历史"),this);
    m_pHistoryButton->setFixedSize(170, 80);
    m_pHistoryButton->setObjectName("m_pHistoryButton");
    connect(m_pHistoryButton, &QPushButton::clicked, this, &CPageTitleWidget::SignalHistoryButton);
    m_pHistoryButton->setFlat(true);
//    m_pHistoryButton->setStyleSheet("background-color:transparent");//
    //
    m_pLogoLabel = new QLabel(this);
    m_pLogoLabel->setFixedSize(190, 80);
    SetWidgetBackImage(m_pLogoLabel, ":/image/ico/main/logo.png");
    //
    m_pUserNameLineEdit = new QLineEdit(this);
    m_pUserNameLineEdit->setReadOnly(true);
    m_pUserNameLineEdit->setObjectName("m_pUserNameLineEdit");
    m_pUserNameLineEdit->setText("Evey");
    //
    m_pUserNameImageLabel = new QLabel(this);
    m_pUserNameImageLabel->setMaximumSize(26,26);
    m_pUserNameImageLabel->setCursor(QCursor(Qt::ArrowCursor));

    QSpacerItem *pSpaceItem = new QSpacerItem(20, 10, QSizePolicy::Expanding);
    QHBoxLayout *pLineLayout = new QHBoxLayout();
    pLineLayout->setContentsMargins(20, 0, 1, 0);
    pLineLayout->addWidget(m_pUserNameImageLabel);
    pLineLayout->addSpacerItem(pSpaceItem);
    m_pUserNameLineEdit->setLayout(pLineLayout);

    m_pUserNameImageLabel->setPixmap(QPixmap(":/image/ico/login/icon_userNormal.png"));

}
/**
  * @brief 布局
  * @param
  * @return
  */
void CPageTitleWidget::_InitLayout()
{

    QHBoxLayout *m_pLayout = new QHBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(0);
    m_pLayout->addWidget(m_pLogoLabel);
    m_pLayout->addSpacing(2);
    m_pLayout->addWidget(m_pUserNameLineEdit);
    m_pLayout->addStretch(1);
    m_pLayout->addWidget(m_pStatusButton);
    m_pLayout->addWidget(m_pTestButton);
    m_pLayout->addWidget(m_pHistoryButton);
    this->setLayout(m_pLayout);
}

