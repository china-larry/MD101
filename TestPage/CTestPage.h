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

signals:


private:
    void _InitWidget();
    void _InitLayout();
private:

    CShowImageWidget *m_pCShowImageWidget;
    CCardInfoWidget *m_pCCardInfoWidget;
    CSampleInfoWidget *m_pCSampleInfoWidget;

    QPushButton *m_pNextStepButton;
    QPushButton *m_pStopTestButton;
};

#endif // CTESTPAGE_H
