#ifndef CSHOWIMAGEWIDGET_H
#define CSHOWIMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "PublicConfig.h"
class CShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShowImageWidget(QWidget *parent = nullptr);

signals:
public:
    void SetCurrentShow(int iTestStep);
private:
    void _InitWidget();
    void _InitLayout();
private:
    QLabel *m_pTitleLabel;
    QLabel *m_pShowVedioLabel;
    QLabel *m_pInfoLabel;
    //
    QStringList m_strTitleList;
    QStringList m_strInfoList;

};

#endif // CSHOWIMAGEWIDGET_H
