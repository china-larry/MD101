#include "CPageStatusWidget.h"
#include <QDebug>
#include <QDateTime>

#include "PublicFunction.h"



CPageStatusWidget::CPageStatusWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1280, 70);
    LoadQss(this, ":/qss/MainPage/MainPage.qss");
    _InitWidget();
    _InitLayout();
    //
    this->setAutoFillBackground(true);  // 自动填充背景
    SetWidgetBackColor(this, QColor(0xff, 0xff, 0xff));
    SetWifiStutus(false);

    qProgressTimer = new QTimer;
    connect(qProgressTimer,SIGNAL(timeout()),this,SLOT(_SlotSetProgressValue()));
    qProgressTimer->start(1000);
    //    m_pWifiLabel->hide();
}


void CPageStatusWidget::_SlotSetProgressValue()
{
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}


void CPageStatusWidget::SetWifiStutus(bool bWifi)
{
    if(bWifi)
    {
        SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi_open.png");
    }
    else
    {
        SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi_close.png");
    }
}

void CPageStatusWidget::UpdateTime()
{
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void CPageStatusWidget::SetLogInfo(QString strLogInfo)
{
    m_pLogsLabel->setText(strLogInfo);
}


void CPageStatusWidget::_InitWidget()
{   
    //
    m_pMenuButton = new QPushButton(tr("菜单"), this);
    m_pMenuButton->setFixedSize(150, 70);
    m_pMenuButton->setObjectName("m_pMenuButton");
    connect(m_pMenuButton, &QPushButton::clicked,
            this, &CPageStatusWidget::SignalShowMenu);
    //
    m_pLogsLabel = new QLabel(this);
    m_pLogsLabel->setFixedSize(400, 50);
    m_pLogsLabel->setObjectName("m_pTestInfoLabel");
//    m_pTestInfoLabel->setText("Test Begin");
    //
    m_pWifiLabel = new QLabel(this);
    m_pWifiLabel->setFixedSize(28, 19);
    SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi_open.png");
    m_pSystemTimeLabel = new QLabel(this);
    m_pSystemTimeLabel->setFixedSize(200, 50);
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    m_pSystemTimeLabel->setObjectName("m_pSystemTimeLabel");
}

void CPageStatusWidget::_InitLayout()
{
    QHBoxLayout *m_pLayout = new QHBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->addSpacing(0);
    m_pLayout->addWidget(m_pMenuButton);
    m_pLayout->addSpacing(5);
    m_pLayout->addWidget(m_pLogsLabel, 0, Qt::AlignLeft);
    m_pLayout->addStretch(1);
    m_pLayout->addWidget(m_pWifiLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pSystemTimeLabel);
    this->setLayout(m_pLayout);
}
