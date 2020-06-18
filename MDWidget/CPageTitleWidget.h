
#ifndef CDETECTORPAGETITLEWIDGET_H
#define CDETECTORPAGETITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
class CPageTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPageTitleWidget(QWidget *parent = 0);

signals:    
    void SignalHomeButton();
    void SignalReturnButton();
public slots:

private slots:

public:
    void SetUserName(QString strUserName);

private:
    void _InitWidget();
    void _InitLayout();

private:

    QLabel *m_pUserMapLabel;
    QLabel *m_pUserNameLabel;
    QPushButton *m_pMainPageButton;
    QPushButton *m_pReturnButton;

};

#endif // CDETECTORPAGETITLEWIDGET_H
