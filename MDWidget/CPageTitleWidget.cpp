
#include "CPageTitleWidget.h"
#include <QPalette>
#include <QDebug>
#include <QLinearGradient>
#include "PublicFunction.h"

CPageTitleWidget::CPageTitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1280, 80);

    _InitWidget();
    _InitLayout();
    //
//    this->setAutoFillBackground(true);  //自动填充背景
//    QLinearGradient qLineGradient(132, 0, 1024, 0);	//控制渐变色的走向
//                qLineGradient.setColorAt(0.0, 0x1862DC);				//渐变的颜色1
//                qLineGradient.setColorAt(0.3, 0x1862DC);				//渐变的颜色1
//                qLineGradient.setColorAt(1.0, 0x28A6FF);				//渐变的颜色2

    //    SetWidgetBackLineColor(this, qLineGradient);
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

    m_pMainPageButton = new QPushButton(this);
    m_pMainPageButton->setFixedSize(173, 80);
    m_pMainPageButton->setObjectName("m_pMainPageButton");
    connect(m_pMainPageButton, &QPushButton::clicked, this, &CPageTitleWidget::SignalHomeButton);

    m_pReturnButton = new QPushButton(this);
    m_pReturnButton->setFixedSize(173, 80);
    m_pReturnButton->setObjectName("m_pReturnButton");
    connect(m_pReturnButton, &QPushButton::clicked, this, &CPageTitleWidget::SignalReturnButton);
    //
    //
    m_pUserMapLabel = new QLabel(this);
    m_pUserMapLabel->setFixedSize(28, 28);
    SetWidgetBackImage(m_pUserMapLabel, ":/image/ico/login/user.png");
    //
    m_pUserNameLabel = new QLabel(this);
    m_pUserNameLabel->setFixedSize(200, 50);

}
/**
  * @brief 布局
  * @param
  * @return
  */
void CPageTitleWidget::_InitLayout()
{
    LoadQss(this, ":/qss/DetectorPage/MainTitle.qss");
    QHBoxLayout *m_pLayout = new QHBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(0);
    m_pLayout->addStretch(100);
   m_pLayout->addWidget(m_pMainPageButton);
   //m_pLayout->addSpacing(0);
   m_pLayout->addWidget(m_pReturnButton);
//    m_pLayout->addWidget(m_pUserNameLabel);
    this->setLayout(m_pLayout);
}

