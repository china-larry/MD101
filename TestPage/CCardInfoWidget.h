#ifndef CCARDINFOWIDGET_H
#define CCARDINFOWIDGET_H

#include <QWidget>

#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "PublicConfig.h"
class CCardInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CCardInfoWidget(QWidget *parent = nullptr);

signals:

public:
    SCardInfoStruct GetCardInfo();
private:
    void _InitWidget();
    void _InitLayout();

private:
    CLabelMarkWidget *m_pCLabelMarkWidget;
    CHLabelLineEditWidget *m_pProjectNameWidget;
    CHLabelLineEditWidget *m_pCardIDWidget;
    QLabel *m_pCardIDLabel;
    CHLabelLineEditWidget *m_pProjectLotWidget;
    CHLabelLineEditWidget *m_pExpirationDateWidget;
    CHLabelLineEditWidget *m_pCardVersionWidget;
};

#endif // CCARDINFOWIDGET_H
