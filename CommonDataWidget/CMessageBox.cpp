#include "CMessageBox.h"

#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QApplication>
#include "PublicFunction.h"
CMessageBox::CMessageBox(QWidget *parent, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    : QDialog(parent)
{


    this->setWindowIcon(QIcon(":/image/ico/main/app-round.ico"));
    setWindowTitle(title);
    setMinimumSize(380, 180);
//    setMinimizeVisible(false);
//    setMaximizeVisible(false);
//    setWidgetResizable(false);

    Qt::WindowFlags flags=Qt::Dialog;
//    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);


    m_pButtonBox = new QDialogButtonBox(this);
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

//    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
//    if (pYesButton != NULL)
//    {
//        pYesButton->setObjectName("blueButton");
//        pYesButton->setStyle(QApplication::style());
//    }

    m_pIconLabel = new QLabel(this);
    m_pLabel = new QLabel(this);

    QPixmap pixmap(":/image/ico/main/app-round.png");
    m_pIconLabel->setPixmap(pixmap);
    m_pIconLabel->setFixedSize(40, 40);
    m_pIconLabel->setScaledContents(true);

    m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabel->setObjectName("whiteLabel");
    m_pLabel->setOpenExternalLinks(true);
    m_pLabel->setText(text);

    m_pGridLayout = new QGridLayout();
    m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignTop);
    m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
    m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
    m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    m_pGridLayout->setHorizontalSpacing(10);
    m_pGridLayout->setVerticalSpacing(10);
    m_pGridLayout->setContentsMargins(10, 10, 10, 10);
//    m_pLayout->addLayout(m_pGridLayout);
    this->setLayout(m_pGridLayout);

    translateUI();

    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    LoadQss(this, ":/qss/CommonDataWidget/CMessageBox.qss");
}

CMessageBox::~CMessageBox()
{

}

void CMessageBox::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        translateUI();
        break;
    default:
        QDialog::changeEvent(event);
    }
}

void CMessageBox::translateUI()
{
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != NULL)
        pYesButton->setText(tr("Yes"));

    QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
    if (pNoButton != NULL)
        pNoButton->setText(tr("No"));

    QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != NULL)
        pOkButton->setText(tr("Ok"));

    QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != NULL)
        pCancelButton->setText(tr("Cancel"));
}

QMessageBox::StandardButton CMessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

QAbstractButton *CMessageBox::clickedButton() const
{
    return m_pClickedButton;
}

int CMessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}

void CMessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    done(execReturnCode(button));
}

void CMessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
        return;
    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void CMessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

void CMessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void CMessageBox::setText(const QString &text)
{
    m_pLabel->setText(text);
}

void CMessageBox::setIcon(const QString &icon)
{
    m_pIconLabel->setPixmap(QPixmap(icon));
}

void CMessageBox::addWidget(QWidget *pWidget)
{
    m_pLabel->hide();
    m_pGridLayout->addWidget(pWidget, 0, 1, 2, 1);
}

QMessageBox::StandardButton ShowInformation(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/information.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton ShowError(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/error.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton ShowSuccess(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/success.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton ShowQuestion(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/question.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton ShowWarning(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/information.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton ShowCritical(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
        msgBox.setIcon(":/image/ico/test/error.ico");
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
}

//QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
//{
//    CMessageBox msgBox(parent, title, text, buttons, defaultButton);
//        msgBox.setIcon(":/image/ico/test/question.ico");

//        QCheckBox *pCheckBox = new QCheckBox(&msgBox);
//        pCheckBox->setText(text);
//        msgBox.addWidget(pCheckBox);
//        if (msgBox.exec() == -1)
//            return QMessageBox::Cancel;

//        QMessageBox::StandardButton standardButton = msgBox.standardButton(msgBox.clickedButton());
//        if (standardButton == QMessageBox::Yes)
//        {
//            return pCheckBox->isChecked() ? QMessageBox::Yes : QMessageBox::No;
//        }
//        return QMessageBox::Cancel;
//}
