#ifndef CSAMPLEINFOWIDGET_H
#define CSAMPLEINFOWIDGET_H

#include <QWidget>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
class CSampleInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CSampleInfoWidget(QWidget *parent = nullptr);

signals:

private:
    void _InitWidget();
    void _InitLayout();

private:
    CLabelMarkWidget *m_pCLabelMarkWidget;
    CLabelCommoBoxWidget *m_pProjectNameWidget; // 项目名称
    CHLabelLineEditWidget *m_pSampleIDWidget; // 样本编号
    CLabelCommoBoxWidget *m_pSampleTypeWidget;// 样本类型
    CHLabelLineEditWidget *m_pNameWidget;// 姓名
    CLabelCommoBoxWidget *m_pGenderWidget;//  性别
    CLabelLineCommoBoxWidget *m_pAgeWidget;// 年龄
    CLabelCommoBoxWidget *m_pDepartmentWidget;// 科室
    CHLabelLineEditWidget *m_pAdmissionNumberWidget;// 住院号
    CHLabelLineEditWidget *m_pBedNumberWidget;// 床号
    CLabelCommoBoxWidget *m_pReferralDoctorWidget; // 送检医生
    CLabelCommoBoxWidget *m_pInspctorNameWidget;// 检验医生
    CLabelCommoBoxWidget *m_pReviewersNameWidget;// 复核者
    CLabelDateWidget *m_pSamplingTimeWidget; // 采样时间
    CLabelDateWidget *m_pSubmissionTimeWidget; // 送检时间
};

#endif // CSAMPLEINFOWIDGET_H
