/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和LineEdit
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLabelLineEditWidget.h"
#include <QBoxLayout>
#include <QIntValidator>
#include <QListView>
#include "PublicFunction.h"
CLabelLineEditWidget::CLabelLineEditWidget(QWidget *parent)
    : QWidget(parent),
      m_strLineText("")
{
}

CLabelLineEditWidget::CLabelLineEditWidget(QString strLabel, QString strLineText, QWidget *parent)
    : QWidget(parent),
     m_strLineText(strLineText)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pLineEdit = new QLineEdit(strLineText, this);
    this->_InitLayout();
}

QString CLabelLineEditWidget::GetLineText()
{
    m_strLineText = m_pLineEdit->text();
    return m_strLineText;
}

void CLabelLineEditWidget::SetLineText(QString strLineText)
{
    m_strLineText = strLineText;
    m_pLineEdit->setText(m_strLineText);
    this->update();
}

void CLabelLineEditWidget::SetLineTextEnable(bool bEnable)
{
    m_pLineEdit->setEnabled(bEnable);
    if(!bEnable)
    {
        m_pLineEdit->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CLabelLineEditWidget::SetLineEditFixSize(int iWidth, int iHeight)
{
    m_pLineEdit->setFixedSize(iWidth, iHeight);
}

void CLabelLineEditWidget::SetLabelObjectName(QString strObjectName)
{
    m_pLabel->setObjectName(strObjectName);
}

void CLabelLineEditWidget::SetLineEditObjectName(QString strObjectName)
{
    m_pLineEdit->setObjectName(strObjectName);
}

void CLabelLineEditWidget::SetLineValidator(int iMin, int iMax)
{
    m_pLineEdit->setValidator(new QIntValidator(iMin, iMax, this));
}

void CLabelLineEditWidget::SetLineValidator(QString ValidatorType)
{
    //只能输入汉字：^[\u4e00-\u9fa5]{0,}$
    //不能输入汉字：^[^\u4e00-\u9fa5]{0,}$
    QRegExp regx(ValidatorType);
    QValidator *validator = new QRegExpValidator(regx, m_pLineEdit );
    m_pLineEdit->setValidator( validator );
}

QLineEdit *CLabelLineEditWidget::GetLineEdit()
{
    return m_pLineEdit;
}

void CLabelLineEditWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addSpacing(2);
    pLayout->addWidget(m_pLineEdit);
    pLayout->addStretch(1);
    this->setLayout(pLayout);
}

CHLabelLineEditWidget::CHLabelLineEditWidget(QString strLabel, QString strLineText, QWidget *parent)
{
    if(parent != NULL)
    {
        m_pLabel = new QLabel(strLabel, this);
        m_pLineEdit = new QLineEdit(strLineText, this);
        this->_InitLayout();
    }
}


void CHLabelLineEditWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pLineEdit);
    pLayout->addSpacing(9);
    this->setLayout(pLayout);
}


CLabelMarkWidget::CLabelMarkWidget(QWidget *parent)
{
    m_strLineText = "";
    _InitLayout();
}

CLabelMarkWidget::CLabelMarkWidget(QString strLineText, QWidget *parent)
{
    m_strLineText = strLineText;
    _InitLayout();
}

void CLabelMarkWidget::SetLableName(QString strName)
{
    m_strLineText = strName;
    m_pNameLabel->setText(m_strLineText);
}

void CLabelMarkWidget::SetLableSize(QSize qSize)
{
    m_pNameLabel->setFixedSize(qSize);
}

void CLabelMarkWidget::_InitLayout()
{
    m_pLabel = new QLabel(this);
    m_pLabel->setFixedSize(5, 30);
    SetLabelBackImage(m_pLabel, ":/image/ico/main/label_mark.png");
    //
    m_pNameLabel = new QLabel(m_strLineText, this);
    m_pNameLabel->setObjectName("m_pNameLabel");
    //m_pNameLabel->setFixedSize(200, 30);
//    m_pNameLabel->setStyleSheet("border-radius: 5px;color: #000;");
//    QFont qFont("Source Han Sans CN", 25, 1, false);
//    m_pNameLabel->setFont(qFont);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(m_pLabel);
    pLayout->addWidget(m_pNameLabel);
    this->setLayout(pLayout);
}

CLabelLineCommoBoxWidget::CLabelLineCommoBoxWidget(QWidget *parent)
{

}

CLabelLineCommoBoxWidget::CLabelLineCommoBoxWidget(QString strLabel, QString strLineText, QStringList strCommoList, QWidget *parent)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pLineEdit = new QLineEdit(strLineText, this);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->setView(new QListView());
    m_pComboBox->addItems(strCommoList);
    this->_InitLayout();
}

QString CLabelLineCommoBoxWidget::GetLineText()
{
    m_strLineText = m_pLineEdit->text();
    return m_strLineText;
}

void CLabelLineCommoBoxWidget::SetLineText(QString strLineText)
{
    m_strLineText = strLineText;
    m_pLineEdit->setText(m_strLineText);
    this->update();
}

void CLabelLineCommoBoxWidget::SetLineTextEnable(bool bEnable)
{
    m_pLineEdit->setEnabled(bEnable);
    if(!bEnable)
    {
        m_pLineEdit->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CLabelLineCommoBoxWidget::SetLineEditFixSize(int iWidth, int iHeight)
{
    m_pLineEdit->setFixedSize(iWidth, iHeight);
}

void CLabelLineCommoBoxWidget::SetLabelObjectName(QString strObjectName)
{
    m_pLabel->setObjectName(strObjectName);
}

void CLabelLineCommoBoxWidget::SetLineEditObjectName(QString strObjectName)
{
    m_pLineEdit->setObjectName(strObjectName);
}

void CLabelLineCommoBoxWidget::SetCommoBoxObjectName(QString strObjectName)
{
    m_pComboBox->setObjectName(strObjectName);
}

void CLabelLineCommoBoxWidget::SetLineValidator(int iMin, int iMax)
{
    m_pLineEdit->setValidator(new QIntValidator(iMin, iMax, this));
}

void CLabelLineCommoBoxWidget::SetLineValidator(QString ValidatorType)
{
    //只能输入汉字：^[\u4e00-\u9fa5]{0,}$
    //不能输入汉字：^[^\u4e00-\u9fa5]{0,}$
    QRegExp regx(ValidatorType);
    QValidator *validator = new QRegExpValidator(regx, m_pLineEdit );
    m_pLineEdit->setValidator( validator );
}

int CLabelLineCommoBoxWidget::GetCurrentIndex()
{
    return m_pComboBox->currentIndex();
}

void CLabelLineCommoBoxWidget::SetCurrentIndex(int iIndex)
{
    m_pComboBox->setCurrentIndex(iIndex);
}

void CLabelLineCommoBoxWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pLineEdit);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pComboBox);
    pLayout->addSpacing(9);
    this->setLayout(pLayout);
}
