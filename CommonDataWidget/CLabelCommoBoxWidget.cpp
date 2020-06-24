/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和CommoBox
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLabelCommoBoxWidget.h"
#include <QBoxLayout>
#include <QDebug>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QCompleter>
#include <QAbstractItemView>
#include <QListView>

QTComboBoxButton::QTComboBoxButton(QWidget *parent /* = 0 */) :
    QLineEdit(parent)
{
}

QTComboBoxButton::~QTComboBoxButton()
{
}

void QTComboBoxButton::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        QPoint pPointPress = QCursor::pos();
        QComboBox* pCombo = dynamic_cast<QComboBox*>(parent());

        if(pCombo)
        {
            QRect rect = pCombo->rect();
            QPoint pos = QPoint(rect.right(), rect.bottom());
            pos = pCombo->mapToGlobal(pos);
            qDebug() << pos << pPointPress;
            if(pPointPress.x() < pos.x() - 40)
            {
              //  pCombo->lineEdit()->setText("");
                QLineEdit::mousePressEvent(e);
            }
            else
            {
                pCombo->showPopup();
            }
        }
    }

}

CLabelCommoBoxWidget::CLabelCommoBoxWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pLabel = new QLabel(this);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->setView(new QListView());
    _InitLayout();
}

CLabelCommoBoxWidget::CLabelCommoBoxWidget(QString strLabel, QStringList strComboList, QWidget *parent)
    : QWidget(parent)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->setMaximumWidth(180);
    m_pComboBox->setMaxVisibleItems(18);//设置最大显示下列项 超过要使用滚动条拖拉
    m_pComboBox->setView(new QListView());
//    m_pComboBox->setEditable(true);
//    m_pComboBox->setLineEdit(new QTComboBoxButton(m_pComboBox));
//    m_pComboBox->lineEdit()->setReadOnly(true);

    connect(m_pComboBox, SIGNAL(currentIndexChanged(int)),  this, SIGNAL(SignalCurrentSelectChange(int)));
    if(strComboList.count())
    {
        m_pComboBox->addItems(strComboList);
       // m_pComboBox->setCurrentIndex(0);
    }
//    m_pComboBox->lineEdit()->setText("");

    _InitLayout();
}

QString CLabelCommoBoxWidget::GetCurrentSelectText()
{
    m_strCurrentSelectText = m_pComboBox->currentText();
    return m_strCurrentSelectText;
}

int CLabelCommoBoxWidget::GetCurrentSelectIndex()
{
    return m_pComboBox->currentIndex();
}

void CLabelCommoBoxWidget::SetCupType(QStringList strCupList)
{
    if(m_pComboBox != NULL)
    {
        m_pComboBox->clear();
        if(strCupList.count() > 0)
        {
            m_pComboBox->addItems(strCupList);
            m_pComboBox->setCurrentIndex(0);
        }
    }
}

void CLabelCommoBoxWidget::SetCurrentIndex(int iIndex)
{
    m_pComboBox->setCurrentIndex(iIndex);
}

void CLabelCommoBoxWidget::SetCurrentText(QString strCupType)
{
    m_pComboBox->setCurrentText(strCupType);
}

void CLabelCommoBoxWidget::AddItemText(QString strText)
{
    m_pComboBox->addItem(strText);
}

void CLabelCommoBoxWidget::SetFixSize(int iWidth, int iHeight)
{
    m_pComboBox->setFixedSize(iWidth, iHeight);
}

void CLabelCommoBoxWidget::ResetComboList(QStringList strList)
{
    m_pComboBox->clear();
    m_pComboBox->addItems(strList);
}

void CLabelCommoBoxWidget::SetEnable(bool bEnable)
{
    m_pComboBox->setEnabled(bEnable);
    if(!bEnable)
    {
         m_pComboBox->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CLabelCommoBoxWidget::SetLineEnableEdit(bool bEdit)
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

void CLabelCommoBoxWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pComboBox);
    pLayout->addSpacing(9);
    this->setLayout(pLayout);
}

CLabelCommoBoxEditWidget::CLabelCommoBoxEditWidget(QWidget *parent)
{
    m_pLabel = new QLabel(this);
    m_pComboBox = new QComboBox(this);
    this->_InitLayout();
}

CLabelCommoBoxEditWidget::CLabelCommoBoxEditWidget(QString strLabel, QStringList strComboList, QWidget *parent)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pComboBox=new QComboBox(this);
     m_pComboBox->setView(new QListView());
//    m_pComboBox->setFixedSize(200, 50);
//    m_pComboBox->setMaxVisibleItems(18);//设置最大显示下列项 超过要使用滚动条拖拉
//    m_pComboBox->setEditable(true);
    m_pComboBox->setLineEdit(new QTComboBoxButton(m_pComboBox));
//    m_pComboBox->lineEdit()->setReadOnly(true);

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
//    pCompleter->popup()->setStyleSheet("QListView{font:75 10pt \"Arial\";subcontrol-origin: padding;subcontrol-position: top right;width: 30px;}");	//设置弹出的补全列表样式

//    m_pComboBox->setCompleter(pCompleter);	//设置自动补全
    m_pComboBox->setStyleSheet("QComboBox{combobox-popup: 0;}");	//linux系统上，防止下拉框过长
    m_pComboBox->setMaxVisibleItems(10);	//下拉最大高度

    this->_InitLayout();
}

QString CLabelCommoBoxEditWidget::GetCurrentSelectText()
{
    m_strCurrentSelectText = m_pComboBox->currentText();
    return m_strCurrentSelectText;
}

int CLabelCommoBoxEditWidget::GetCurrentSelectIndex()
{
    return m_pComboBox->currentIndex();
}

void CLabelCommoBoxEditWidget::SetCurrentIndex(int iIndex)
{
    m_pComboBox->setCurrentIndex(iIndex);
}

void CLabelCommoBoxEditWidget::SetCurrentText(QString strCupType)
{
    m_pComboBox->setCurrentText(strCupType);
}

void CLabelCommoBoxEditWidget::AddItemText(QString strText)
{
    m_pComboBox->addItem(strText);
}

void CLabelCommoBoxEditWidget::SetFixSize(int iWidth, int iHeight)
{
    m_pComboBox->setFixedSize(iWidth, iHeight);
}

void CLabelCommoBoxEditWidget::ResetComboList(QStringList strList)
{
    m_pComboBox->clear();
    m_pComboBox->addItems(strList);
}

void CLabelCommoBoxEditWidget::SetEnable(bool bEnable)
{
    m_pComboBox->setEnabled(bEnable);
    if(!bEnable)
    {
         m_pComboBox->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CLabelCommoBoxEditWidget::SetLineEnableEdit(bool bEdit)
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

void CLabelCommoBoxEditWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addSpacing(3);
    pLayout->addWidget(m_pComboBox);
    this->setLayout(pLayout);
}

CVLabelCommoBoxWidget::CVLabelCommoBoxWidget(QWidget *parent)
{
    m_pLabel = new QLabel(this);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->setView(new QListView());
    _InitLayout();
}

CVLabelCommoBoxWidget::CVLabelCommoBoxWidget(QString strLabel, QStringList strComboList, QWidget *parent)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->setMaximumWidth(180);
    m_pComboBox->setMaxVisibleItems(18);//设置最大显示下列项 超过要使用滚动条拖拉

    m_pComboBox->setView(new QListView());
//    m_pComboBox->setEditable(true);
//    m_pComboBox->setLineEdit(new QTComboBoxButton(m_pComboBox));
//    m_pComboBox->lineEdit()->setReadOnly(true);

    connect(m_pComboBox, SIGNAL(currentIndexChanged(int)),  this, SIGNAL(SignalCurrentSelectChange(int)));
    if(strComboList.count())
    {
        m_pComboBox->addItems(strComboList);
       // m_pComboBox->setCurrentIndex(0);
    }
//    m_pComboBox->lineEdit()->setText("");

    _InitLayout();
}

QString CVLabelCommoBoxWidget::GetCurrentSelectText()
{
    m_strCurrentSelectText = m_pComboBox->currentText();
    return m_strCurrentSelectText;
}

int CVLabelCommoBoxWidget::GetCurrentSelectIndex()
{
    return m_pComboBox->currentIndex();
}

void CVLabelCommoBoxWidget::SetCupType(QStringList strCupList)
{
    if(m_pComboBox != NULL)
    {
        m_pComboBox->clear();
        if(strCupList.count() > 0)
        {
            m_pComboBox->addItems(strCupList);
            m_pComboBox->setCurrentIndex(0);
        }
    }
}

void CVLabelCommoBoxWidget::SetCurrentIndex(int iIndex)
{
     m_pComboBox->setCurrentIndex(iIndex);
}

void CVLabelCommoBoxWidget::SetCurrentText(QString strCupType)
{
    m_pComboBox->setCurrentText(strCupType);
}

void CVLabelCommoBoxWidget::AddItemText(QString strText)
{
    m_pComboBox->addItem(strText);
}

void CVLabelCommoBoxWidget::SetFixSize(int iWidth, int iHeight)
{
    m_pComboBox->setFixedSize(iWidth, iHeight);
}

void CVLabelCommoBoxWidget::SetMinSize(int iWidth, int iHeight)
{
    m_pComboBox->setMinimumSize(iWidth, iHeight);
}

void CVLabelCommoBoxWidget::SetMaxSize(int iWidth, int iHeight)
{
    m_pComboBox->setMaximumSize(iWidth, iHeight);
}

void CVLabelCommoBoxWidget::ResetComboList(QStringList strList)
{
    m_pComboBox->clear();
    m_pComboBox->addItems(strList);
}

void CVLabelCommoBoxWidget::SetEnable(bool bEnable)
{
    m_pComboBox->setEnabled(bEnable);
    if(!bEnable)
    {
         m_pComboBox->setStyleSheet("background-color:rgba(200,200,200,200)");
    }
}

void CVLabelCommoBoxWidget::SetLineEnableEdit(bool bEdit)
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

void CVLabelCommoBoxWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addSpacing(2);
    pLayout->addWidget(m_pComboBox);
    this->setLayout(pLayout);
}
