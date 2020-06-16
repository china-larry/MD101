#include "CDayTimeDialog.h"
#include <QBoxLayout>
CTimeObject::CTimeObject(QWidget *parent)
: QWidget(parent)
{

}

CTimeObject::CTimeObject(QString strName, QSize qSize, QWidget *parent)
    : m_strName(strName)
    , m_qSize(qSize)
    , QWidget(parent)
{
    LoadQss(this, ":/qss/SettingPage/CSystemTime.qss");
    _InitWidget();
    _InitLayout();
}

void CTimeObject::_SlotAdd()
{
    m_iValue++;
    if(m_strName == tr("Year"))
    {
        if(m_iValue > 2099)
        {
            m_iValue = 2099;
        }
    }
    if(m_strName == tr("Month"))
    {
        if(m_iValue > 12)
        {
            m_iValue = 1;
        }
    }
    else if(m_strName == tr("Day"))
    {
        if(m_iValue > 31)
        {
            m_iValue = 1;
        }
    }
    else if(m_strName == tr("Hour"))
    {
        if(m_iValue > 23)
        {
            m_iValue = 0;
        }
    }
    else if(m_strName == tr("Minute"))
    {
        if(m_iValue > 59)
        {
            m_iValue = 0;
        }
    }
    else if(m_strName == tr("Second"))
    {
        if(m_iValue > 59)
        {
            m_iValue = 0;
        }
    }
    m_pValueLineEdit->setText(QString::number(m_iValue));
}

void CTimeObject::_SlotSub()
{
    m_iValue--;
    if(m_strName == tr("Year"))
    {
        if(m_iValue < 1970)
        {
            m_iValue = 1970;
        }
    }
    if(m_strName == tr("Month"))
    {
        if(m_iValue < 1)
        {
            m_iValue = 12;
        }
    }
    else if(m_strName == tr("Day"))
    {
        if(m_iValue < 1)
        {
            m_iValue = 31;
        }
    }
    else if(m_strName == tr("Hour"))
    {
        if(m_iValue < 0)
        {
            m_iValue = 23;
        }
    }
    else if(m_strName == tr("Minute"))
    {
        if(m_iValue < 0)
        {
            m_iValue = 59;
        }
    }
    else if(m_strName == tr("Second"))
    {
        if(m_iValue < 0)
        {
            m_iValue = 59;
        }
    }
    m_pValueLineEdit->setText(QString::number(m_iValue));
}

void CTimeObject::SetValue(int iValue)
{
    m_iValue = iValue;
    m_pValueLineEdit->setText(QString::number(m_iValue));
}

int CTimeObject::GetValue()
{
    m_iValue = m_pValueLineEdit->text().toInt();
    return m_iValue;
}

void CTimeObject::_InitWidget()
{
    m_pNameLabel = new QLabel(m_strName, this);
    m_pNameLabel->setFixedSize(m_qSize);
    m_pNameLabel->setAlignment(Qt::AlignCenter);
    m_pAddButton = new QPushButton(this);
    m_pAddButton->setFixedSize(m_qSize);
    connect(m_pAddButton, SIGNAL(clicked()), this, SLOT(_SlotAdd()));
    m_pValueLineEdit = new QLineEdit(this);
    m_pValueLineEdit->setAlignment(Qt::AlignCenter);
    m_pValueLineEdit->setFixedSize(m_qSize);
    m_pSubButton = new QPushButton(this);
    m_pSubButton->setFixedSize(m_qSize);
    connect(m_pSubButton, SIGNAL(clicked()), this, SLOT(_SlotSub()));
    if(m_qSize.width() > 80)
    {// 年控件
        m_pAddButton->setObjectName("m_pAddYearButton");
        m_pSubButton->setObjectName("m_pSubYearButton");
    }
    else
    {
        m_pAddButton->setObjectName("m_pAddNotYearButton");
        m_pSubButton->setObjectName("m_pSubNotYearButton");
    }

    m_pAddButton->setAutoRepeat(true);
    m_pAddButton->setAutoRepeatDelay(500);
    m_pAddButton->setAutoRepeatInterval(100);
    m_pSubButton->setAutoRepeat(true);
    m_pSubButton->setAutoRepeatDelay(500);
    m_pSubButton->setAutoRepeatInterval(100);
}

void CTimeObject::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(25);
    pLayout->addWidget(m_pNameLabel, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pAddButton, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pValueLineEdit, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pSubButton, 0, Qt::AlignHCenter);

    this->setLayout(pLayout);
}

CDayDialog* CDayDialog::m_pInstance = NULL;
CDayDialog::CDayDialog(QWidget *parent) : QDialog(parent)
{
    LoadQss(this, ":/qss/SettingPage/CSystemTime.qss");
    this->setFixedSize(500, 400);
    setAttribute(Qt::WA_ShowModal, true);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setGeometry(256, 150, 500, 400);
//    SetWidgetBackColor(this, QColor(255, 255, 255));
    _InitWidget();
    _InitLayout();
}

void CDayDialog::showEvent(QShowEvent *pEvent)
{
//    QDateTime qCurrentDateTime = QDateTime::currentDateTime();
//    m_pYearWidget->SetValue(qCurrentDateTime.date().year());
//    m_pMonthWidget->SetValue(qCurrentDateTime.date().month());
//    m_pDayWidget->SetValue(qCurrentDateTime.date().day());
}

void CDayDialog::SlotOk()
{
    this->accept();
}

void CDayDialog::SlotCancel()
{
    this->reject();
}

CDayDialog *CDayDialog::GetInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CDayDialog();
    }
    return m_pInstance;
}

void CDayDialog::SetDate(QString strDate)
{
    QDate qDate = QDate::fromString(strDate, "yyyy-MM-dd");
    m_pYearWidget->SetValue(qDate.year());
    m_pMonthWidget->SetValue(qDate.month());
    m_pDayWidget->SetValue(qDate.day());
}

QString CDayDialog::GetDate()
{    
    QDate qDate = QDate(m_pYearWidget->GetValue(),
                        m_pMonthWidget->GetValue(),
                        m_pDayWidget->GetValue());

    return qDate.toString("yyyy-MM-dd");
}

void CDayDialog::_InitWidget()
{
    m_pYearWidget = new  CTimeObject(tr("Year"), QSize(80, 50), this);
    m_pMonthWidget = new  CTimeObject(tr("Month"), QSize(80, 50), this);
    m_pDayWidget = new  CTimeObject(tr("Day"), QSize(80, 50), this);

    QDateTime qCurrentDateTime = QDateTime::currentDateTime();
    m_pYearWidget->SetValue(qCurrentDateTime.date().year());
    m_pMonthWidget->SetValue(qCurrentDateTime.date().month());
    m_pDayWidget->SetValue(qCurrentDateTime.date().day());

    m_pOKButton = new QPushButton(tr("Confirm"), this);
    m_pOKButton->setFixedSize(140, 50);
    connect(m_pOKButton, SIGNAL(clicked()), this, SLOT(SlotOk()));
    m_pCancelButton = new QPushButton(tr("Cancel"), this);
    m_pCancelButton->setFixedSize(140, 50);
    connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(SlotCancel()));
}


void CDayDialog::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(15);
    //
    QHBoxLayout *pTimeLayout = new QHBoxLayout;
    pTimeLayout->setMargin(0);
    pTimeLayout->setSpacing(15);
    pTimeLayout->addStretch(1);
    pTimeLayout->addWidget(m_pYearWidget);
    pTimeLayout->addWidget(m_pMonthWidget);
    pTimeLayout->addWidget(m_pDayWidget);
    pTimeLayout->addStretch(1);

    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(1);
    pButtonLayout->addWidget(m_pOKButton);
    pButtonLayout->addSpacing(40);
    pButtonLayout->addWidget(m_pCancelButton);
    pButtonLayout->addStretch(1);


    pLayout->addSpacing(15);
    pLayout->addLayout(pTimeLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pButtonLayout);
    pLayout->addSpacing(25);
    this->setLayout(pLayout);

}

CDayTimeDialog* CDayTimeDialog::m_pInstance = NULL;
CDayTimeDialog::CDayTimeDialog(QWidget *parent) : QDialog(parent)
{
    LoadQss(this, ":/qss/SettingPage/CSystemTime.qss");
    this->setFixedSize(600, 400);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    _InitWidget();
    _InitLayout();
}

void CDayTimeDialog::showEvent(QShowEvent *pEvent)
{
    QDateTime qCurrentDateTime = QDateTime::currentDateTime();
    m_pYearWidget->SetValue(qCurrentDateTime.date().year());
    m_pMonthWidget->SetValue(qCurrentDateTime.date().month());
    m_pDayWidget->SetValue(qCurrentDateTime.date().day());
    m_pTimeWidget->SetValue(qCurrentDateTime.time().hour());
    m_pMinWidget->SetValue(qCurrentDateTime.time().minute());
    m_pSecWidget->SetValue(qCurrentDateTime.time().second());
}

void CDayTimeDialog::SlotOk()
{
    this->accept();
}

void CDayTimeDialog::SlotCancel()
{
    this->reject();
}

CDayTimeDialog *CDayTimeDialog::GetInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CDayTimeDialog();
    }
    return m_pInstance;
}

void CDayTimeDialog::SetDateTime(QString strDate)
{

}

QString CDayTimeDialog::GetDateTime()
{

}

void CDayTimeDialog::_InitWidget()
{
//    m_pLabelMarkWidget = new CLabelMarkWidget(tr("设置-仪器管理-日期时间"), this);
    m_pYearWidget = new  CTimeObject(tr("Year"), QSize(80, 50), this);
    m_pMonthWidget = new  CTimeObject(tr("Month"), QSize(80, 50), this);
    m_pDayWidget = new  CTimeObject(tr("Day"), QSize(80, 50), this);
    m_pTimeWidget = new  CTimeObject(tr("Hour"), QSize(80, 50), this);
    m_pMinWidget = new  CTimeObject(tr("Minute"), QSize(80, 50), this);
    m_pSecWidget = new  CTimeObject(tr("Second"), QSize(80, 50), this);

    QDateTime qCurrentDateTime = QDateTime::currentDateTime();
    m_pYearWidget->SetValue(qCurrentDateTime.date().year());
    m_pMonthWidget->SetValue(qCurrentDateTime.date().month());
    m_pDayWidget->SetValue(qCurrentDateTime.date().day());
    m_pTimeWidget->SetValue(qCurrentDateTime.time().hour());
    m_pMinWidget->SetValue(qCurrentDateTime.time().minute());
    m_pSecWidget->SetValue(qCurrentDateTime.time().second());

    m_pOKButton = new QPushButton(tr("Confirm"), this);
    m_pOKButton->setFixedSize(140, 50);
    connect(m_pOKButton, SIGNAL(clicked()), this, SLOT(SlotOk()));
    m_pCancelButton = new QPushButton(tr("Cancel"), this);
    m_pCancelButton->setFixedSize(140, 50);
    connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(SlotCancel()));
}


void CDayTimeDialog::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(15);
//    pLayout->addWidget(m_pLabelMarkWidget, 0, Qt::AlignLeft);
    //
    QHBoxLayout *pTimeLayout = new QHBoxLayout;
    pTimeLayout->setMargin(0);
    pTimeLayout->setSpacing(15);
    pTimeLayout->addStretch(1);
    pTimeLayout->addWidget(m_pYearWidget);
    pTimeLayout->addWidget(m_pMonthWidget);
    pTimeLayout->addWidget(m_pDayWidget);
    pTimeLayout->addSpacing(90);
    pTimeLayout->addWidget(m_pTimeWidget);
    pTimeLayout->addWidget(m_pMinWidget);
    pTimeLayout->addWidget(m_pSecWidget);
    pTimeLayout->addStretch(1);

    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(1);
    pButtonLayout->addWidget(m_pOKButton);
    pButtonLayout->addSpacing(40);
    pButtonLayout->addWidget(m_pCancelButton);
    pButtonLayout->addStretch(1);


    pLayout->addSpacing(9);
    pLayout->addLayout(pTimeLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pButtonLayout);
    pLayout->addSpacing(6);
    this->setLayout(pLayout);

}


CDayLineEdit::CDayLineEdit(QWidget *parent)
{
    m_pCDayDialog = CDayDialog::GetInstance();
    LoadQss(this, ":/qss/SettingPage/CSystemTime.qss");
}

CDayLineEdit::CDayLineEdit(QString str, QWidget *parent)
 : QLineEdit(str, parent)
{
    m_pCDayDialog = CDayDialog::GetInstance();
    LoadQss(this, ":/qss/SettingPage/CSystemTime.qss");
}

void CDayLineEdit::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        //this->setFocus();
        if(m_pCDayDialog != NULL)
        {
//            qDebug() << "product data SetCurrentLineEdit" << this->text();
           m_pCDayDialog->SetDate(this->text());
            if(m_pCDayDialog->exec() == QDialog::Accepted)
            {
//                qDebug() << "product data copyss" << m_pCDayDialog->GetDate();
                this->setText(m_pCDayDialog->GetDate());
            }
        }
    }
}
