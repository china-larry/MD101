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
#ifndef CLABELLINEEDITWIDGET_H
#define CLABELLINEEDITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "KeyBoard/CVLineEdit.h"
// 前竖条标记特殊Label显示
class CLabelMarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelMarkWidget(QWidget *parent = 0);
    explicit CLabelMarkWidget(QString strLineText, QWidget *parent = 0);

signals:

public slots:

public:
void SetLableName(QString strName);
void SetLableSize(QSize qSize);
protected:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    QLabel *m_pNameLabel;
    QString m_strLineText;
};
/*****************************************************
  * Class: CHLabelLineEditWidget
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现复合组合控件Label和LineEdit，垂直布局
  * Others:
  ****************************************************/
class CLabelLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelLineEditWidget(QWidget *parent = 0);
    explicit CLabelLineEditWidget(QString strLabel, QString strLineText, QWidget *parent = 0);

signals:

public slots:

public:
    QString GetLineText();
    void SetLineText(QString strLineText);
    void SetLineTextEnable(bool bEnable);
    void SetLineEditFixSize(int iWidth, int iHeight);
    void SetLabelObjectName(QString strObjectName);
    void SetLineEditObjectName(QString strObjectName);
    void SetLineValidator(int iMin, int iMax);// 设置输入范围
    void SetLineValidator(QString ValidatorType);
    CVLineEdit *GetLineEdit();

protected:
    void _InitLayout();
protected:
    QLabel *m_pLabel;
    CVLineEdit *m_pLineEdit;
    QString m_strLineText;
};
/*****************************************************
  * Class: CHLabelLineEditWidget
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现复合组合控件Label和LineEdit，水平布局
  * Others:
  ****************************************************/
class CHLabelLineEditWidget : public CLabelLineEditWidget
{
    Q_OBJECT
public:
    explicit CHLabelLineEditWidget(QWidget *parent = 0);
    explicit CHLabelLineEditWidget(QString strLabel, QString strLineText, QWidget *parent = 0);

signals:

public slots:


protected:
    void _InitLayout();
};

#endif // CLABELLINEEDITWIDGET_H
