#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QDebug>

#include "PublicFunction.h"
#include "MuItemDelegate.h"

const QStringList icons = {
    ":/image/images/HotDog.jpg", ":/image/images/li.jpg", ":/image/images/logo.jpg",
    ":/image/images/PACT.jpg", ":/image/images/yang.jpg", ":/image/images/zhang.jpg",
};
const QStringList singers = {
    "MC-Hotdog", "李荣浩", "Author",
    "PACT", "杨千嬅", "张震岳",
};


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
    LoadQss(this, ":/qss/MainPage.qss");
    //
    m_kiTitleHeight = 80;// title高度
    m_kiStatusBarHeight = 70;// 状态栏高度
    m_bShowMenu = false;
    _InitWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *)
{
    // 固定位置
    m_iWidgetRect = this->rect();
//    // 标题栏
    m_pCPageTitleWidget->setGeometry(0, 0, m_iWidgetRect.width(), m_kiTitleHeight);
    // 多标签
    m_pStackedWidget->setGeometry(10, m_kiTitleHeight+10, m_iWidgetRect.width()-20,
                                  m_iWidgetRect.height() - m_kiTitleHeight - m_kiStatusBarHeight-20);
    // 状态栏
    m_pCPageStatusWidget->setGeometry(0, m_iWidgetRect.height() - m_kiStatusBarHeight,
                                          m_iWidgetRect.width(), m_kiStatusBarHeight);

    m_pQListView->setGeometry(0, m_iWidgetRect.height() - m_kiStatusBarHeight - m_pQListView->height(),
                              m_pQListView->width(), m_pQListView->height());

}

void MainWindow::SlotShwoMenu()
{
    m_bShowMenu = !m_bShowMenu;
    if(m_bShowMenu)
    {
        m_pQListView->show();
    }
    else
    {
        m_pQListView->hide();
    }
}

void MainWindow::_SlotMenuChanged(QModelIndex index)
{
//    qDebug() << "r c" << index.row() << index.column();
    m_pQListView->hide();
    m_bShowMenu = !m_bShowMenu;
}
void MainWindow::_InitWidget()
{
    // 标题栏
    m_pCPageTitleWidget = new CPageTitleWidget(this);
    // 多标签
    m_pStackedWidget = new QStackedWidget(this);
    m_pStackedWidget->setStyleSheet("QWidget{background-color:white;border-radius:15px;}");
    // 状态栏
    m_pCPageStatusWidget = new CPageStatusWidget(this);
    connect(m_pCPageStatusWidget, &CPageStatusWidget::SignalShowMenu,
            this, &MainWindow::SlotShwoMenu);

    m_pQListView = new QListView(this);
    m_pQListView->setFixedSize(230, 720);
    m_pQListView->hide();
    QStandardItemModel *pModel = new QStandardItemModel();
    for (int i=0; i<icons.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.singer = singers.at(i);
        itemData.songsNb = QString::number(i * i) + "首";
        itemData.iconPath = icons.at(i);
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pModel->appendRow(pItem);
    }

    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    m_pQListView->setItemDelegate(pItemDelegate);
    m_pQListView->setModel(pModel);
    connect(m_pQListView, &QListView::clicked,
            this, &MainWindow::_SlotMenuChanged);

}
