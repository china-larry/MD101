#ifndef CUSERNAMESHOWWIDGET_H
#define CUSERNAMESHOWWIDGET_H

#include <QWidget>
#include <QLabel>
class CUserNameShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CUserNameShowWidget(QWidget *parent = nullptr);

signals:



private:
    QLabel *m_pImageLabel;
    QLabel *m_pUserNameLabel;

};

#endif // CUSERNAMESHOWWIDGET_H
