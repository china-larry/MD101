#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PublicFunction.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(1280, 800);
    SetWidgetBackColor(this, QColor(0xE1, 0xE2, 0xEA));

    QApplication::setApplicationDisplayName(tr("MDx"));
    this->setWindowTitle(tr("MDx"));

    this->setWindowIcon(QIcon(":/image/ico/main/app-round.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

