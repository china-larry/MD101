#ifndef PUBLICCONFIG_H
#define PUBLICCONFIG_H
#include <QString>
#include <QMetaType>
//
const QString gc_strUDiskPath = "/run/media/sda1";//udisk
const QString gc_strAppName = "MDx101";
const QString gc_strAppArmPath = "/home/root/";
const QString gc_strDataPath = "/home/root/db/";
const QString gc_strAppReleaseNumber = "V 1.0.1";
const QString gc_strAppFullNumber = "V 1.0.1";
const QString gc_strFirmewareNumber = "V 1.0.1";
// 数据库
const QString gc_strHistoryDBName = "history.db"; //
const QString gc_strSystemDBName = "system.db"; // user
const QString gc_strProjectDBName = "projectinfo.db"; //
const QString gc_strHistoryDB = gc_strDataPath + gc_strHistoryDBName;
const QString gc_strHistoryDBConnect = "history_connect";
const QString gc_strProjectDB = gc_strDataPath + gc_strProjectDBName;
const QString gc_strProjectDBConnect = "project_connect";
const QString gc_strSystemDB = gc_strDataPath + gc_strSystemDBName;
const QString gc_strSystemDBConnect ="system_connect";




typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)



#endif // PUBLICCONFIG_H
