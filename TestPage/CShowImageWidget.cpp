#include "CShowImageWidget.h"
#include <QLayout>
#include "PublicFunction.h"
CShowImageWidget::CShowImageWidget(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
    this->setFixedSize(390, 600);
   // SetWidgetBackColor(this, QColor(255, 255, 255));
    m_strTitleList << tr("第一步 扫描试剂盒ID")
                  << tr("第二步 扫描样本编号")
                  << tr("第三步 加样操作")
                  << tr("第四步 拔出试剂盒芯片")
                  << tr("第五步 将试剂盒放入测试仪");
    m_strInfoList << tr("听到”哔“的一声，扫码完成")
                  << tr("听到”哔“的一声，扫码完成")
                  << tr("加样完成后需推回密封片")
                  << tr("芯片需拔出至指定位置")
                  << tr("试剂盒放入后请关闭仓门");
    //
    _InitWidget();
    _InitLayout();

}

void CShowImageWidget::SetCurrentShow(int iTestStep)
{
    m_pTitleLabel->setText(m_strTitleList[iTestStep]);
    m_pInfoLabel->setText(m_strInfoList[iTestStep]);
    switch (iTestStep)
    {
    case CardINfo:

        break;
    case SampleInfo:

        break;
    case AddSample:

        break;
    case OutCardChip:

        break;
    case StartTest:

        break;
    default:
        break;
    }
}

void CShowImageWidget::_InitWidget()
{
    m_pTitleLabel = new QLabel(m_strTitleList[0], this);
    m_pTitleLabel->setFixedSize(340, 70);
    m_pTitleLabel->setObjectName("m_pTitleLabel");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);

    //
    m_pShowVedioLabel = new QLabel(this);
    m_pShowVedioLabel->setFixedSize(340, 400);
    m_pShowVedioLabel->setObjectName("m_pShowVedioLabel");

    //
    m_pInfoLabel = new QLabel(m_strInfoList[0], this);
    m_pInfoLabel->setFixedSize(390, 70);
    m_pInfoLabel->setObjectName("m_pInfoLabel");
    m_pInfoLabel->setAlignment(Qt::AlignCenter);

}

void CShowImageWidget::_InitLayout()
{
    QVBoxLayout *m_pLayout = new QVBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(0);
    m_pLayout->addSpacing(20);
    m_pLayout->addWidget(m_pTitleLabel, 0, Qt::AlignHCenter);
    m_pLayout->addSpacing(13);
    m_pLayout->addWidget(m_pShowVedioLabel, 0, Qt::AlignHCenter);
    m_pLayout->addStretch(1);
    m_pLayout->addWidget(m_pInfoLabel, 0, Qt::AlignHCenter);
    this->setLayout(m_pLayout);
}
