#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QWidget>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QGridLayout>

class QLabel;

class CMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CMessageBox(QWidget *parent = 0, const QString &title = tr("Tip"), const QString &text = "",
                        QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
    ~CMessageBox();
    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    // 设置默认按钮
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);
    // 设置窗体标题
    void setTitle(const QString &title);
    // 设置提示信息
    void setText(const QString &text);
    // 设置窗体图标
    void setIcon(const QString &icon);
    // 添加控件-替换提示信息所在的QLabel
    void addWidget(QWidget *pWidget);

protected:
    // 多语言翻译
    void changeEvent(QEvent *event);

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    void translateUI();
    int execReturnCode(QAbstractButton *button);

private:
    QLabel *m_pIconLabel;
    QLabel *m_pLabel;
    QGridLayout *m_pGridLayout;
    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
};

QMessageBox::StandardButton ShowInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                            QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton ShowError(QWidget *parent, const QString &title,
                                      const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                      QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton ShowSuccess(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                        QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton ShowQuestion(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                                         QMessageBox::StandardButton defaultButton = QMessageBox::Yes );

QMessageBox::StandardButton ShowWarning(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                        QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton ShowCritical(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                         QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

//QMessageBox::StandardButton ShowCheckBoxQuestion(QWidget *parent, const QString &title,
//                                                 const QString &text, QMessageBox::StandardButtons buttons,
//                                                 QMessageBox::StandardButton defaultButton);

#endif // CMESSAGEBOX_H
