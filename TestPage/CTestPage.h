#ifndef CTESTPAGE_H
#define CTESTPAGE_H

#include <QWidget>
#include <QPushButton>

#include "CCardInfoWidget.h"
#include "CShowImageWidget.h"
#include "CSampleInfoWidget.h"
class CTestPage : public QWidget
{
    Q_OBJECT
public:
    explicit CTestPage(QWidget *parent = nullptr);

    void showEvent(QShowEvent *pEvent);
//    void hideEvent(QHideEvent *pEvent);
signals:

private slots:
    void _SlotPreStep();
    void _SlotNextStep();
    void _SlotStopTest();
    void _SlotOpenDoor();
    void _SlotCloseDoor();
    void _SlotStartTest();

private:
    void _InitWidget();
    void _InitLayout();
    void _UpdateWidget();
private:

    CShowImageWidget *m_pCShowImageWidget;
    CCardInfoWidget *m_pCCardInfoWidget;
    CSampleInfoWidget *m_pCSampleInfoWidget;
    QPushButton *m_pPreStepButton;
    QPushButton *m_pNextStepButton;
    QPushButton *m_pStopTestButton;
    QPushButton *m_pOpenDoorButton;
    QPushButton *m_pCloseDoorButton;
    QPushButton *m_pStartTestButton;

    // 0:card info,1:sample info,2:add sample,
    // 3:out card,4:input for test
    int m_iCurrentStepIndex;
};

#endif // CTESTPAGE_H
