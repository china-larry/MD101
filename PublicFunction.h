#ifndef PUBLICFUNCTION_H
#define PUBLICFUNCTION_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QProxyStyle>
#include <QSqlDatabase>
#include <QThread>
#include <QProcess>
#include <QImage>
#include "PublicConfig.h"
/**
  * @brief 设置控件背景图片
  * @param pWidget:控件，非空
  * @param strImagepath:路径地址
  * @return
  */
void SetWidgetBackImage(QWidget *pWidget, QString strImagePath);
/**
  * @brief 设置控件背景色
  * @param pWidget：控件名称
  * @param qColor: 颜色
  * @return
  */
void SetWidgetBackColor(QWidget *pWidget, QColor qColor);
void SetWidgetBackLineColor(QWidget *pWidget, QLinearGradient qLinearGradient);
/**
  * @brief pushbutton背景图片
  * @param pButton:控件
  * @param strImagePath：路径
  * @return
  */
void SetButtonBackImage(QPushButton *pButton, QString strImagePath);
/**
  * @brief 设置Label背景图片
  * @param pLabel：控件
  * @param strImagePath：路径
  * @return
  */
void SetLabelBackImage(QLabel *pLabel, QString strImagePath);
void SetLabelBackImage(QLabel *pLabel,  QPixmap *pPixmap);
/**
  * @brief 设置Label背景图片,绘制红色提示区域框，只为测试结果使用
  * @param
  * @return
  */
void SetLabelBackImageEx(QLabel *pLabel, QString strImagePath, QRect qRedRect);
/**
  * @brief 设置控件QSS样式
  * @param pWidget：控件
  * @param strQssFilePath：地址
  * @return
  */
void LoadQss(QWidget *pWidget, QString strQssFilePath);
/**
  * @brief 获取图片的base64值(PNG)
  * @param strImagePath：地址
  * @return
  */
QString GetImagePngBase64(QString strImagePath);
/**
  * @brief 连接数据库
  * @param strDBName：数据库路径名称
  * @return
  */
QSqlDatabase ConnectDataBase(const QString &kstrDBName, const QString &kstrConnectName);

/**
  * @brief 向TableWidget添加一行
  * @param pTableWidget：控件
  * @param strContentList：添加行数据的字符串数组
  * @return true：添加成功；false：添加失败
  */
bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList);
bool InsertOneLineCheck(QTableWidget *pTableWidget, QStringList strContentList);
//
bool InsertOneLineTop(QTableWidget *pTableWidget, QStringList strContentList, int iRow,int iColumnCount);
// 插入一列
bool InsertOneColumn(QTableWidget *pTableWidget, QStringList strContentList);

bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList, QComboBox *qComBox);
/**
  * @brief 向TableWidget某行某列添加Item
  * @param iRow：所在行
  * @param iColumn：所在列
  * @param strContent：Item显示的内容
  * @return true：添加成功；false：添加失败
  */
bool InsertOneItem(QTableWidget *pTableWidget, int iRow, int iColumn, QString strContent);
// QTableWidget翻页,iOnePageNumber 一页数量
void TableToPrePage(QTableWidget *pTableWidget, int iOnePageNumber);
void TableToNextPage(QTableWidget *pTableWidget, int iOnePageNumber);
void TableToLeftPage(QTableWidget *pTableWidget, int iOnePageNumber);
void TableToRightPage(QTableWidget *pTableWidget, int iOnePageNumber);
// 获得选中行
bool GetCurrentSelectRows(QTableWidget *pTableWidget, QVector<int> &qSelectVector);
// 删除选中行
void DeleteTabelSelctRows(QTableWidget *pTableWidget);

//
void RemoveFile(QString strFilePath);
/**
  * @brief 打印报告
  * @param
  * @return
  */
bool PrintToPage(QString strHtml);
/**
  * @brief 保存报告PDF
  * @param strHtml: 待保存的数据流
  * @param pWidget: 保存对话框父类
  * @return
  */
bool PrintToPdf(QString strHtml, QWidget *pWidget);

/**
  * @brief 自定义TabBar
  * @param
  * @return
  */
class CCustomTabStyle : public QProxyStyle
{

public :
    explicit CCustomTabStyle();
    virtual ~CCustomTabStyle();
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const;
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;

};

/**
 * @brief getCRC16  获取CRC16
 * @param data  计算的数据
 * @param len  数据的长度
 * @param oldCRC16  上一个CRC16的值，用于循环计算大文件的CRC16。第一个数据的CRC16则传入0x0。
 * @return
 */
unsigned short GetCRC16(const char *pData, unsigned long ulLen,unsigned long ulOldCRC16 = 0);


bool WriteJsonMap(QString strConfigFileName,
                        QString strParamsType,
                        QMap<QString,QVariant> qParamsMap);
bool ReadJsonMap(QString strConfigFileName,
                  QString strParamsType,
                  QMap<QString,QVariant> *pParamsMap);

void SetSystemDataTime(QDateTime qDateTime);
/*方法1*/
bool MkDirExist(QString fullPath);
void WaitSleep(qint32 iMsec);


/**
  * @brief 拷贝文件夹
  * @param
  * @return
  */
bool CopyFileDir(const QString &kstrSrcDir, const QString &kstrDestDir, bool bCoverFileIfExist);
//


int GetByte2Int(char *pByte);

quint16 GetSmallByte(quint16 qDate);

//
#endif // PUBLICFUNCTION_H
