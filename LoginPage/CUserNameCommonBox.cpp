#include "CUserNameCommonBox.h"
#include <QBoxLayout>
#include <QDebug>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QCompleter>
#include <QAbstractItemView>
#include <QListView>

#include "CommonDataWidget/CLabelCommoBoxWidget.h"
#include "PublicFunction.h"
CUserNameCommonBox::CUserNameCommonBox(QWidget *parent) : QWidget(parent)
{

}

CUserNameCommonBox::CUserNameCommonBox(QStringList strComboList, QWidget *parent)
{
    m_pComboBox=new QComboBox(this);
     m_pComboBox->setView(new QListView());
    m_pComboBox->setLineEdit(new QTComboBoxButton(m_pComboBox));
    m_pComboBox->lineEdit()->setStyleSheet("QLineEdit{padding-left:60px;}\
                                QLineEdit:focus{padding-left:60px;}");


   connect(m_pComboBox, SIGNAL(currentIndexChanged(int)),  this, SIGNAL(SignalCurrentSelectChange(int)));

    QStandardItemModel *pModel=new QStandardItemModel(this);    //源数据
    QList<QStandardItem *> pStandardItemRowList;
    QStandardItem *blankitem=new QStandardItem("");
//    pModel->appendRow(blankitem);	//增加一行空白

    for(int i = 0; i < strComboList.count(); ++i)
    {
        if(!strComboList[i].isEmpty()){
            pStandardItemRowList.clear();
            QStandardItem *pItem = new QStandardItem(strComboList[i]);
            pModel->appendRow(pItem );	//添加一行，2列数据
        }
    }
    m_pComboBox->setModel(pModel);	//QComboBox设置数据源
    m_pComboBox->setEditable(true);
    m_pComboBox->lineEdit()->setReadOnly(false);

//    QCompleter *pCompleter=new QCompleter(m_pComboBox);
//    pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
//    pCompleter->setModel(pModel);
//    pCompleter->setCompletionColumn(m_pComboBox->modelColumn());
//    pCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
//    pCompleter->setMaxVisibleItems(5);	//下拉最大高度
//    pCompleter->popup()->setStyleSheet("QListView{font:75 10pt \"Source Han Sans CN\";subcontrol-origin: padding;subcontrol-position: top right;width: 30px;}");	//设置弹出的补全列表样式

//    m_pComboBox->setCompleter(pCompleter);	//设置自动补全
    m_pComboBox->setStyleSheet("QComboBox{combobox-popup: 0;}");	//linux系统上，防止下拉框过长
    m_pComboBox->setMaxVisibleItems(10);	//下拉最大高度


    m_pLabel = new QLabel(this);
    m_pLabel->setMaximumSize(28,28);
    m_pLabel->setCursor(QCursor(Qt::ArrowCursor));

    QSpacerItem *pSpaceItem = new QSpacerItem(10, 10, QSizePolicy::Expanding);
    QHBoxLayout *pCommonLayout = new QHBoxLayout();
    pCommonLayout->setContentsMargins(20, 0, 6, 0);
    pCommonLayout->addWidget(m_pLabel);
    pCommonLayout->addSpacerItem(pSpaceItem);
    m_pComboBox->setLayout(pCommonLayout);

    m_pLabel->setPixmap(QPixmap(":/image/ico/login/icon_userNormal.png"));


    this->_InitLayout();
}

QString CUserNameCommonBox::GetCurrentSelectText()
{
    m_strCurrentSelectText = m_pComboBox->currentText();
    return m_strCurrentSelectText;
}

int CUserNameCommonBox::GetCurrentSelectIndex()
{
    return m_pComboBox->currentIndex();
}


void CUserNameCommonBox::SetCurrentIndex(int iIndex)
{
    m_pComboBox->setCurrentIndex(iIndex);
}

void CUserNameCommonBox::SetCurrentText(QString strCupType)
{
    m_pComboBox->setCurrentText(strCupType);
}

void CUserNameCommonBox::AddItemText(QString strText)
{
    m_pComboBox->addItem(strText);
}

void CUserNameCommonBox::SetFixSize(int iWidth, int iHeight)
{
    m_pComboBox->setFixedSize(iWidth, iHeight);
}

void CUserNameCommonBox::ResetComboList(QStringList strList)
{
    m_pComboBox->clear();
    m_pComboBox->addItems(strList);
}

void CUserNameCommonBox::SetEnable(bool bEnable)
{
    m_pComboBox->setEnabled(bEnable);
    if(!bEnable)
    {
         m_pComboBox->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CUserNameCommonBox::SetLineEnableEdit(bool bEdit)
{
    if(bEdit)
    {
        m_pComboBox->setEditable(true);
        m_pComboBox->lineEdit()->setReadOnly(false);
    }
    else
    {
        m_pComboBox->setEditable(false);
        m_pComboBox->lineEdit()->setReadOnly(true);
    }
}

void CUserNameCommonBox::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    pLayout->addWidget(m_pComboBox);
    this->setLayout(pLayout);
}

///////////////////////////////////////////////////////////////////////////////////
CPasswordWidget::CPasswordWidget(QWidget *parent) : QWidget(parent)
{
    m_bSeePassWord = false;
    LoadQss(this, ":/qss/LoginPage/LoginPage.qss");
    m_pPasswordLineEdit = new QLineEdit(this);
//    m_pPasswordLineEdit->setStyleSheet("QLineEdit{padding-left:50px;}\
//                                QLineEdit:focus{padding-left:50px;}");
    m_pPasswordLineEdit->setObjectName("m_pPasswordLineEdit");

    m_pLabel = new QLabel(this);
    m_pLabel->setMaximumSize(28,28);
    m_pLabel->setCursor(QCursor(Qt::ArrowCursor));

    m_pPasswordHidButton = new QPushButton(this);
    m_pPasswordHidButton->setFixedSize(56, 56);
    m_pPasswordHidButton->setObjectName("m_pPasswordHidButton");
    m_pPasswordHidButton->setCursor(QCursor(Qt::ArrowCursor));
    m_pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    SetButtonBackImage(m_pPasswordHidButton, ":/image/ico/login/no_see.png");
    connect(m_pPasswordHidButton, &QPushButton::clicked,
            this, &CPasswordWidget::_SlotCheckHideButton);

    QSpacerItem *pSpaceItem = new QSpacerItem(10, 10, QSizePolicy::Expanding);
    QHBoxLayout *pCommonLayout = new QHBoxLayout();
    pCommonLayout->setContentsMargins(20, 0, 0, 0);
    pCommonLayout->addWidget(m_pLabel);
    pCommonLayout->addSpacerItem(pSpaceItem);
    pCommonLayout->addWidget(m_pPasswordHidButton);
    m_pPasswordLineEdit->setLayout(pCommonLayout);

    m_pLabel->setPixmap(QPixmap(":/image/ico/login/icon_password_normal.png"));

    this->_InitLayout();
}

void CPasswordWidget::_SlotCheckHideButton()
{
    if(m_bSeePassWord)
    {
        m_bSeePassWord = false;
        SetButtonBackImage(m_pPasswordHidButton, ":/image/ico/login/no_see.png");// 默认不可见
        m_pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
    else
    {
        m_bSeePassWord = true;
        SetButtonBackImage(m_pPasswordHidButton, ":/image/ico/login/see.png");// 默认不可见
        m_pPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
}

QString CPasswordWidget::GetCurrentText()
{
    m_strCurrentSelectText = m_pPasswordLineEdit->text();
    return m_strCurrentSelectText;
}


void CPasswordWidget::SetFixSize(int iWidth, int iHeight)
{
    m_pPasswordLineEdit->setFixedSize(iWidth, iHeight);
}


void CPasswordWidget::SetEnable(bool bEnable)
{
    m_pPasswordLineEdit->setEnabled(bEnable);
    if(!bEnable)
    {
         m_pPasswordLineEdit->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CPasswordWidget::SetLineEnableEdit(bool bEdit)
{
    if(bEdit)
    {
        m_pPasswordLineEdit->setReadOnly(false);
    }
    else
    {
        m_pPasswordLineEdit->setReadOnly(true);
    }
}

void CPasswordWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    pLayout->addWidget(m_pPasswordLineEdit);
    this->setLayout(pLayout);
}
