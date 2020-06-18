#ifndef CPAGESTATUSWIDGET_H
#define CPAGESTATUSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QTimer>
#include <QListView>
class CPageStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPageStatusWidget(QWidget *parent = nullptr);

signals:
    void SignalShowMenu();
public slots:
private slots:

    void _SlotSetProgressValue();
public:
    void SetWifiStutus(bool bWifi);
    void UpdateTime();
    void SetLogInfo(QString strLogInfo);
private:
    void _InitWidget();
    void _InitLayout();
private:
    //
    QPushButton *m_pMenuButton;



    QLabel *m_pLogsLabel;
    QLabel *m_pWifiLabel;
    QLabel *m_pSystemTimeLabel;
    QTimer *qProgressTimer;
};

#endif // CPAGESTATUSWIDGET_H
