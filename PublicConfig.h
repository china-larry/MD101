#ifndef PUBLICCONFIG_H
#define PUBLICCONFIG_H
#include <QString>
#include <QMetaType>
//
const QString gc_strUDiskPath = "/run/media/sda1";//udisk
const QString gc_strAppName = "MDx101";
const QString gc_strAppArmPath = "/home/twdz/Work_Pro/MDx101/bin/GCC_64bit-Debug/";///home/root/
const QString gc_strDataPath = "/home/twdz/Work_Pro/MDx101/bin/GCC_64bit-Debug/db/";//// /home/root/db/
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



static const int gk_iReSendTimes = 3;// 重发次数
static const int gk_iWaitMsecs = 1000;// 重发等待时间间隔

struct SCanBusDeviceStruct
{
    QString strPlugin;// 接口类型
    QString strInterfaceName;// 接口名称
    qint32 iFrameId;// CAN总线标识符
    qint32 iBitRate;// 波特率
};

struct SCanBusDataStruct
{
    quint8 quCmdID;
    quint8 quObjectID;
    quint8 quErrorID;
    quint8 quFormat;
    QByteArray qbPayload;
};

struct SMqttMsgStruct
{
    QString strTopic;
    QString strMessage;
};

typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} SMuItemDataStruct;
// 测试步骤
enum EnumTestStep
{
    CardINfo = 0,        // 扫描试剂盒ID
    SampleInfo = 1,       // 样本信息
    AddSample = 2, // 加样
    OutCardChip = 3, // 拔出芯片
    StartTest = 4, // 开始测试
};
// 卡盒信息
struct SCardInfoStruct
{
    QString strCardID;
    QString strProjectName;
    QString strProjectLot;
    QString strExpirationDate;
    QString strCardVersion;
};
// 病人信息
struct SPatientInfoStruct
{
    QString strPatientID;
    QString strName;
    QString strGender;
    QString strAge;
    QString strAgeType;
    QString strDepartment;
    QString strAdmissionNumber;
    QString strBedNumber;
    QString strReferralDoctor;
    QString strInspctorName;
    QString strReviewersName;
    QString strSamplingTime;
    QString strSubmissionTime;
};
// 样本信息
struct SSampleInfoStruct
{
    QString strSampleID;
    QString strSampleType;
    QString strSerialNo;
    QString strSampleNumber;
    QString strApplicationTime;
    QString strSourceFrom;
    QString strCardID;
    QString strPatientID;
};

Q_DECLARE_METATYPE(SMuItemDataStruct)



#endif // PUBLICCONFIG_H
