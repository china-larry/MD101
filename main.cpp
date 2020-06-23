#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFont font;
    font.setPointSize(10);//实际字体的大小需要试试
    font.setFamily(("Source Han Sans CN"));
    font.setBold(false);
    a.setFont(font);


    MainWindow w;
//    w.show();
    return a.exec();
}
