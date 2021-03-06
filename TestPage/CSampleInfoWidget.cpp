#include "CSampleInfoWidget.h"
#include <QBoxLayout>
CSampleInfoWidget::CSampleInfoWidget(QWidget *parent) : QWidget(parent)
{
    LoadQss(this, ":/qss/TestPage/TestPage.qss");
    this->setFixedSize(810, 525);
    _InitWidget();
    _InitLayout();
}

void CSampleInfoWidget::_InitWidget()
{
    m_pCLabelMarkWidget = new CLabelMarkWidget(tr("样本信息"), this);
    QStringList strProjectNameList;
    strProjectNameList << "FLuA/B";
    m_pProjectNameWidget = new CLabelCommoBoxWidget(tr("项目名称"), strProjectNameList, this);
//    m_pProjectNameWidget->hide();
    m_pSampleIDWidget = new CHLabelLineEditWidget(tr("样本编号"), tr(""), this);
    QStringList strSampleTypeList;
    strSampleTypeList << tr("全血") << tr("血清");
    m_pSampleTypeWidget = new CLabelCommoBoxWidget(tr("样本类型"), strSampleTypeList, this);
    m_pNameWidget = new CHLabelLineEditWidget(tr("姓名"), tr(""), this);
    QStringList strGenderList;
    strGenderList << tr("男") << tr("女");
    m_pGenderWidget = new CLabelCommoBoxWidget(tr("性别"), strGenderList, this);
    QStringList strAgeList;
    strAgeList << "岁" << "月";
    m_pAgeWidget = new CLabelLineCommoBoxWidget(tr("年龄"), "", strAgeList, this);
    m_pAgeWidget->SetLineEditObjectName("m_pAgeLineWidget");
//    m_pAgeWidget->SetLineEditFixSize(90, 50);
    m_pAgeWidget->SetCommoBoxObjectName("m_pAgeWidget");
    QStringList strDepartmentList;
    strDepartmentList << "体检中心" << "ICU";
    m_pDepartmentWidget = new CLabelCommoBoxWidget(tr("科室"), strDepartmentList, this);
    m_pAdmissionNumberWidget = new CHLabelLineEditWidget(tr("住院号"), tr(""), this);
    m_pBedNumberWidget = new CHLabelLineEditWidget(tr("床号"), tr(""), this);
    QStringList strDoctorList;
    strDoctorList << "李医生" << "王医生";
    m_pReferralDoctorWidget = new CLabelCommoBoxWidget(tr("送检医生"), strDoctorList, this);
    m_pInspctorNameWidget = new CLabelCommoBoxWidget(tr("检验医生"), strDoctorList, this);
    m_pReviewersNameWidget = new CLabelCommoBoxWidget(tr("复核者"), strDoctorList, this);
    m_pSamplingTimeWidget = new CLabelDateWidget(tr("采样时间"), QDate::currentDate(), this);
    m_pSubmissionTimeWidget = new CLabelDateWidget(tr("送检时间"), QDate::currentDate(), this);
}

void CSampleInfoWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
//    pLayout->setSpacing(20);
//    pLayout->addSpacing(15);
    pLayout->addWidget(m_pCLabelMarkWidget, 0, Qt::AlignLeft);
    pLayout->addStretch(1);
    //
    QGridLayout *pGridLayout = new QGridLayout;
    pGridLayout->setContentsMargins(25, 0, 25, 0);
    pGridLayout->setHorizontalSpacing(38);
    pGridLayout->setVerticalSpacing(8);
    pGridLayout->addWidget(m_pSampleIDWidget, 0, 0, 1, 1);
    pGridLayout->addWidget(m_pProjectNameWidget, 0, 1, 1, 1);

    pGridLayout->addWidget(m_pSampleTypeWidget, 1, 0, 1, 1);
    pGridLayout->addWidget(m_pDepartmentWidget, 1, 1, 1, 1);

    pGridLayout->addWidget(m_pNameWidget, 2, 0, 1, 1);
    pGridLayout->addWidget(m_pAdmissionNumberWidget, 2, 1, 1, 1);

    pGridLayout->addWidget(m_pGenderWidget, 3, 0, 1, 1);
    pGridLayout->addWidget(m_pBedNumberWidget, 3, 1, 1, 1);

    pGridLayout->addWidget(m_pAgeWidget, 4, 0, 1, 1);
    pGridLayout->addWidget(m_pReferralDoctorWidget, 4, 1, 1, 1);

    pGridLayout->addWidget(m_pInspctorNameWidget, 5, 0, 1, 1);
    pGridLayout->addWidget(m_pReviewersNameWidget, 5, 1, 1, 1);

    pGridLayout->addWidget(m_pSamplingTimeWidget, 6, 0, 1, 1);
    pGridLayout->addWidget(m_pSubmissionTimeWidget, 6, 1, 1, 1);

    pLayout->addLayout(pGridLayout);

    pLayout->addSpacing(25);
    this->setLayout(pLayout);

}
