QT       += core gui network serialbus sql printsupport
QT += core-private
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CommonDataWidget/CLabelCommoBoxWidget.cpp \
    CommonDataWidget/CMessageBox.cpp \
    DataControl/CHistoryDB.cpp \
    DataControl/CLogDB.cpp \
    DataControl/CProjectDB.cpp \
    DataControl/CUserInfoDB.cpp \
    DataControl/ParamsConfiguration.cpp \
    HistoryPage/CHistoryPage.cpp \
    LoginPage/CLoginInWidget.cpp \
    MDWidget/CPageStatusWidget.cpp \
    MDWidget/CPageTitleWidget.cpp \
    MuItemDelegate.cpp \
    PublicConfig.cpp \
    PublicFunction.cpp \
    PublicWidget.cpp \
    SettingPage/CSettingPage.cpp \
    StatusPage/CStatusPage.cpp \
    TestPage/CTestPage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CommonDataWidget/CLabelCommoBoxWidget.h \
    CommonDataWidget/CMessageBox.h \
    DataControl/CHistoryDB.h \
    DataControl/CLogDB.h \
    DataControl/CProjectDB.h \
    DataControl/CUserInfoDB.h \
    DataControl/ParamsConfiguration.h \
    HistoryPage/CHistoryPage.h \
    LoginPage/CLoginInWidget.h \
    MDWidget/CPageStatusWidget.h \
    MDWidget/CPageTitleWidget.h \
    MuItemDelegate.h \
    PublicConfig.h \
    PublicFunction.h \
    PublicWidget.h \
    SettingPage/CSettingPage.h \
    StatusPage/CStatusPage.h \
    TestPage/CTestPage.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    qssresourcefile.qrc
