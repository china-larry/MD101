#include "CPageStatusWidget.h"
#include <QDebug>
#include <QDateTime>

#include "PublicFunction.h"



CPageStatusWidget::CPageStatusWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1280, 67);
    LoadQss(this, ":/qss/MainPage/MainPage.qss");
    _InitWidget();
    _InitLayout();
    //
//    this->setAutoFillBackground(true);  // 自动填充背景
    //SetWidgetBackColor(this, QColor(0xff, 0xff, 0xff));
 //   SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/footer.png");

    qProgressTimer = new QTimer;
    connect(qProgressTimer,SIGNAL(timeout()),this,SLOT(_SlotSetProgressValue()));
    qProgressTimer->start(1000);
}


void CPageStatusWidget::_SlotSetProgressValue()
{
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}


void CPageStatusWidget::SetWifiStutus(bool bWifi)
{
    if(bWifi)
    {
        SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi1.png");
    }
    else
    {
        SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi-close.png");
    }
}

void CPageStatusWidget::UpdateTime()
{
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void CPageStatusWidget::SetLogInfo(QString strLogInfo)
{
    m_pLogsLabel->setText("       "+strLogInfo);

}


void CPageStatusWidget::_InitWidget()
{   
    //
    m_pMenuButton = new QPushButton(tr("     菜单"), this);
    m_pMenuButton->setFixedSize(136, 67);
    m_pMenuButton->setObjectName("m_pMenuButton");
    connect(m_pMenuButton, &QPushButton::clicked,
            this, &CPageStatusWidget::SignalShowMenu);
    //
    m_pLogsLabel = new QLabel(this);
    m_pLogsLabel->setFixedSize(600, 46);
    m_pLogsLabel->setObjectName("m_pTestInfoLabel");
    SetWidgetBackImage(m_pLogsLabel, ":/image/ico/status/logs-bg.png");
    m_pLogsLabel->setText("       仪器需要校准");
    //
    m_pUDiskLabel = new QLabel(this);
    m_pUDiskLabel->setFixedSize(18, 28);
    SetWidgetBackImage(m_pUDiskLabel, ":/image/ico/status/udisk.png");
    //
    m_pBlueLabel = new QLabel(this);
    m_pBlueLabel->setFixedSize(25, 28);
    SetWidgetBackImage(m_pBlueLabel, ":/image/ico/status/blue.png");
    //
    m_pWifiLabel = new QLabel(this);
    m_pWifiLabel->setFixedSize(37, 30);
    SetWidgetBackImage(m_pWifiLabel, ":/image/ico/status/wifi1.png");
    //
    m_pLISLabel = new QLabel(this);
    m_pLISLabel->setFixedSize(31, 28);
    SetWidgetBackImage(m_pLISLabel, ":/image/ico/status/icon_LIS_close.png");
    //
    m_pSoundLabel = new QLabel(this);
    m_pSoundLabel->setFixedSize(26, 28);
    SetWidgetBackImage(m_pSoundLabel, ":/image/ico/status/sound-close.png");
    //
    m_pSystemTimeLabel = new QLabel(this);
    m_pSystemTimeLabel->setFixedSize(200, 50);
    m_pSystemTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    m_pSystemTimeLabel->setObjectName("m_pSystemTimeLabel");
}

void CPageStatusWidget::_InitLayout()
{
    QHBoxLayout *m_pLayout = new QHBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(15);
    m_pLayout->addWidget(m_pMenuButton);
    m_pLayout->addSpacing(5);
    m_pLayout->addWidget(m_pLogsLabel, 0, Qt::AlignLeft);
    m_pLayout->addStretch(1);
    m_pLayout->addWidget(m_pUDiskLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pBlueLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pWifiLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLISLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pSoundLabel, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pSystemTimeLabel);
    m_pLayout->addSpacing(15);
    this->setLayout(m_pLayout);
}
