#include "CShowImageWidget.h"
#include <QLayout>
#include "PublicFunction.h"
CShowImageWidget::CShowImageWidget(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
    this->setFixedSize(390, 600);
   // SetWidgetBackColor(this, QColor(255, 255, 255));
    _InitWidget();
    _InitLayout();
}

void CShowImageWidget::_InitWidget()
{
    m_pTitleLabel = new QLabel(tr("第一步 扫描试剂盒ID"), this);
    m_pTitleLabel->setFixedSize(340, 70);
    m_pTitleLabel->setObjectName("m_pTitleLabel");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);

    //
    m_pShowVedioLabel = new QLabel(this);
    m_pShowVedioLabel->setFixedSize(340, 400);
    m_pShowVedioLabel->setObjectName("m_pShowVedioLabel");

    //
    m_pInfoLabel = new QLabel(tr("听到“哔”的一声，扫码完成!"), this);
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
    m_pLayout->addSpacing(20);
    m_pLayout->addWidget(m_pShowVedioLabel, 0, Qt::AlignHCenter);
    m_pLayout->addStretch(1);
    m_pLayout->addWidget(m_pInfoLabel, 0, Qt::AlignHCenter);
    this->setLayout(m_pLayout);
}
