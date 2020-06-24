#ifndef CSHOWIMAGEWIDGET_H
#define CSHOWIMAGEWIDGET_H

#include <QWidget>
#include <QLabel>

class CShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShowImageWidget(QWidget *parent = nullptr);

signals:

private:
    void _InitWidget();
    void _InitLayout();
private:
    QLabel *m_pTitleLabel;
    QLabel *m_pShowVedioLabel;
    QLabel *m_pInfoLabel;

};

#endif // CSHOWIMAGEWIDGET_H
