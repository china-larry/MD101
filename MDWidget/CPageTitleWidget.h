
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
    void SignalStatusButton();
    void SignalTestButton();
    void SignalHistoryButton();
public slots:

private slots:

public:
    void SetUserName(QString strUserName);

private:
    void _InitWidget();
    void _InitLayout();

private:
    QLabel *m_pLogoLabel;
    QLabel *m_pUserNameImageLabel;
    QLineEdit *m_pUserNameLineEdit;

    QPushButton *m_pStatusButton;
    QPushButton *m_pTestButton;
    QPushButton *m_pHistoryButton;

};

#endif // CDETECTORPAGETITLEWIDGET_H
