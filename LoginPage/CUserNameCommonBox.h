#ifndef CUSERNAMECOMMONBOX_H
#define CUSERNAMECOMMONBOX_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
class CUserNameCommonBox : public QWidget
{
    Q_OBJECT
public:
    explicit CUserNameCommonBox(QWidget *parent = nullptr);
    explicit CUserNameCommonBox(QStringList strComboList, QWidget *parent = 0);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
public:
    QString GetCurrentSelectText();
    int GetCurrentSelectIndex();
    void SetCurrentIndex(int iIndex);
    void SetCurrentText(QString strCupType);
    void AddItemText(QString strText);
    void SetFixSize(int iWidth, int iHeight);
    void ResetComboList(QStringList strList);
    void SetEnable(bool bEnable);
    void SetLineEnableEdit(bool bEdit);
protected:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    QComboBox *m_pComboBox;
    QString m_strCurrentSelectText;

};

class CPasswordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPasswordWidget(QWidget *parent = nullptr);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
private slots:
    void _SlotCheckHideButton();
public:
    QString GetCurrentText();
    void SetFixSize(int iWidth, int iHeight);
    void SetEnable(bool bEnable);
    void SetLineEnableEdit(bool bEdit);

protected:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    QPushButton *m_pPasswordHidButton;
    QLineEdit *m_pPasswordLineEdit;
    QString m_strCurrentSelectText;
    bool m_bSeePassWord;// false不可见，true可见

};
#endif // CUSERNAMECOMMONBOX_H
