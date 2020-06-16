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
#ifndef CLABELCOMMOBOXWIDGET_H
#define CLABELCOMMOBOXWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
class QTComboBoxButton : public QLineEdit
{
    Q_OBJECT
public:
    QTComboBoxButton(QWidget *parent = 0);
    ~QTComboBoxButton();

protected:
    void mousePressEvent(QMouseEvent *);
};

class CLabelCommoBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelCommoBoxWidget(QWidget *parent = 0);
    explicit CLabelCommoBoxWidget(QString strLabel, QStringList strComboList, QWidget *parent = 0);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
public:
    QString GetCurrentSelectText();
    int GetCurrentSelectIndex();
    void SetCupType(QStringList strCupList);
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
class CVLabelCommoBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVLabelCommoBoxWidget(QWidget *parent = 0);
    explicit CVLabelCommoBoxWidget(QString strLabel, QStringList strComboList, QWidget *parent = 0);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
public:
    QString GetCurrentSelectText();
    int GetCurrentSelectIndex();
    void SetCupType(QStringList strCupList);
    void SetCurrentIndex(int iIndex);
    void SetCurrentText(QString strCupType);
    void AddItemText(QString strText);
    void SetFixSize(int iWidth, int iHeight);
    void SetMinSize(int iWidth, int iHeight);
    void SetMaxSize(int iWidth, int iHeight);
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
class CLabelCommoBoxEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelCommoBoxEditWidget(QWidget *parent = 0);
    explicit CLabelCommoBoxEditWidget(QString strLabel, QStringList strComboList, QWidget *parent = 0);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
public:
    QString GetCurrentSelectText();
    int GetCurrentSelectIndex();
    void SetCupType(QStringList strCupList);
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

#endif // CLABELCOMMOBOXWIDGET_H
