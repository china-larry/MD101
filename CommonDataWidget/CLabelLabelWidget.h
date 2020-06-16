#ifndef CLABELLABELWIDGET_H
#define CLABELLABELWIDGET_H

#include <QWidget>
#include <QLabel>
class CLabelLabelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelLabelWidget(QWidget *parent = nullptr);
    explicit CLabelLabelWidget(QString strLabelName, QString strShowValue, QWidget *parent = nullptr);

signals:

public slots:
public:
    void SetValue(QString strValue, bool bColor = false);
private:
    void _InitWidget();
    void _InitLayout();

private:
    QLabel *m_pLabel;
    QLabel *m_pShowValue;// 数据
    QString m_strLabel;
    QString m_strValue;
};

#endif // CLABELLABELWIDGET_H
