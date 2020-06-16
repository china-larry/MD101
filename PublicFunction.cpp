#include "PublicFunction.h"
#include <QPixmap>
#include <QBitmap>
#include <QPalette>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QBuffer>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QPainter>
#include <QColor>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QNetworkInterface>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <time.h>
#include <cstdlib>
#include <QApplication>
#include <QScrollBar>
#include <QMouseEvent>
#include <QCheckBox>
#include <QBoxLayout>
#include <qalgorithms.h>
#include "CommonDataWidget/CMessageBox.h"
/**
  * @brief 设置控件背景图片
  * @param pWidget：控件名称
  * @param strImagepath：背景图片的地址（资源类型）
  * @return
  */
void SetWidgetBackImage(QWidget *pWidget, QString strImagePath)
{
    if(pWidget == NULL || strImagePath.isNull())
    {
        return;
    }
    //this->setWindowOpacity(0.7); //窗口整体透明度，0-1 从全透明到不透明
    QPixmap qPixmap(strImagePath);
    QPalette  qPalette;
    qPalette.setBrush(pWidget->backgroundRole(),QBrush(qPixmap));
    pWidget->setPalette(qPalette);
    pWidget->setMask(qPixmap.mask());  //可以将图片中透明部分显示为透明的
    pWidget->setAutoFillBackground(true);
}
/**
  * @brief 设置控件背景色
  * @param pWidget：控件名称
  * @param qColor: 颜色
  * @return
  */
void SetWidgetBackColor(QWidget *pWidget, QColor qColor)
{
    if(pWidget == NULL)
    {
        return;
    }
     QPalette  qPalette;
     qPalette.setBrush(pWidget->backgroundRole(), qColor);
     pWidget->setPalette(qPalette);
     pWidget->setAutoFillBackground(true);
}
void SetWidgetBackLineColor(QWidget *pWidget, QLinearGradient qLinearGradient)
{
    if(pWidget == NULL)
    {
        return;
    }
     QPalette  qPalette;
     qPalette.setBrush(pWidget->backgroundRole(), QBrush(qLinearGradient));
     pWidget->setPalette(qPalette);
     pWidget->setAutoFillBackground(true);
}


/**
  * @brief pushbutton背景图片
  * @param
  * @return
  */
void SetButtonBackImage(QPushButton *pButton, QString strImagePath)
{
    if(pButton == NULL || strImagePath.isNull())
    {
        return;
    }
    pButton->setIcon(QIcon(strImagePath));
    pButton-> setIconSize(QSize(pButton->width(), pButton->height()));
}
/**
  * @brief 设置Label背景图片
  * @param
  * @return
  */
void SetLabelBackImage(QLabel *pLabel, QString strImagePath)
{
    if(pLabel == NULL || strImagePath.isNull())
    {
        return;
    }
    QPixmap qPixmap(strImagePath);
    pLabel->setPixmap(qPixmap.scaled(pLabel->width(), pLabel->height(), Qt::KeepAspectRatio));
    pLabel->setAlignment(Qt::AlignCenter);
}
void SetLabelBackImage(QLabel *pLabel, QPixmap *pPixmap)
{
    if(pLabel == NULL || pPixmap == NULL)
    {
        return;
    }
    pLabel->setPixmap(pPixmap->scaled(pLabel->width(), pLabel->height(), Qt::KeepAspectRatio));
    pLabel->setAlignment(Qt::AlignCenter);
}

/**
  * @brief 设置Label背景图片,绘制红色提示区域框，只为测试结果使用
  * @param
  * @return
  */
void SetLabelBackImageEx(QLabel *pLabel, QString strImagePath, QRect qRedRect)
{

    if(pLabel == NULL || strImagePath.isNull())
    {
        return;
    }
    QPixmap qPixmap(strImagePath);
    //
    QPainter painter;
    painter.begin(&qPixmap);
    painter.setPen(QPen(QBrush(QColor(255, 0, 0)), 5));
    //painter.setBrush(QColor(255, 255, 0));
   // painter.drawRect(qRedRect);
//    QPainterPath qPath;
//     // 暂时固定，不固定重绘时候线宽不一致
//     qPath.moveTo(80, 380);
//     qPath.lineTo(130, 380);
//     qPath.lineTo(130, 780);
//     qPath.lineTo(80, 780);
//     qPath.closeSubpath();
//     painter.drawPath(qPath);
     QPainterPath path;
      path.moveTo(qRedRect.topLeft());
      path.lineTo(qRedRect.topRight());
      path.lineTo(qRedRect.bottomRight());
      path.lineTo(qRedRect.bottomLeft());
      path.closeSubpath();
      painter.drawPath(path);
//    qDebug() <<"width " << qRedRect.topLeft() <<  qRedRect.topRight()
//            << qRedRect.bottomRight()  << qRedRect.bottomLeft() <<"rect " <<qRedRect;
//    pPixmap->save("E:\\s9.png");

    pLabel->setPixmap(qPixmap.scaled(pLabel->width(), pLabel->height(), Qt::KeepAspectRatio));
    pLabel->setAlignment(Qt::AlignCenter);

}
/**
  * @brief 设置Widget的QSS样式
  * @param pWidget：控件名称
  * @param strQssFilePath：QSS样式文件地址
  * @return
  */
void LoadQss(QWidget *pWidget, QString strQssFilePath)
{
    if(pWidget == NULL || strQssFilePath.isNull())
    {
        return;
    }
    QFile qFile(strQssFilePath);
    if(!qFile.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream qTextStream(&qFile);
    QString strStylesheet = qTextStream.readAll();
    pWidget->setStyleSheet(strStylesheet);
    qFile.close();
}
/**
  * @brief 获取图片的base64值(PNG)
  * @param strImagePath:输入图片的路径
  * @return QString:获取的base64值
  */
QString GetImagePngBase64(QString strImagePath)
{
    if(strImagePath.isNull())
    {
        return "";
    }
    QImage qImage(strImagePath);
    QByteArray qByteArray;
    QBuffer qBuffer(&qByteArray);
    qImage.save(&qBuffer, "PNG");
    QString strBase64(qByteArray.toBase64());
    return strBase64;
}
QSqlDatabase ConnectDataBase(const QString &kstrDBName, const QString &kstrConnectName)
{
    QSqlDatabase qSqlDataBase = QSqlDatabase::addDatabase("QSQLITE", kstrConnectName);
    qSqlDataBase.setDatabaseName(kstrDBName);
    qSqlDataBase.setPassword(kstrConnectName);
    return qSqlDataBase;
}
/**
  * @brief 向TableWidget添加一行
  * @param 添加行数据的字符串数组
  * @return true：添加成功；false：添加失败
  */
bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList)
{

    int iColumnCount = pTableWidget->columnCount();
    int iContentListCount = strContentList.count();
    if(iContentListCount < 1 || iContentListCount != iColumnCount)
    {// 插入数据不正确，不进行插入操作
        return false;
    }
    // 创建行
    int iRow = pTableWidget->rowCount();
    pTableWidget->insertRow(iRow);
    //
    for(int i = 0; i != iColumnCount; ++i)
    {
        if(!InsertOneItem(pTableWidget, iRow, i, strContentList.at(i)))
        {
            return false;
        }
    }

    return true;
}
bool InsertOneLineCheck(QTableWidget *pTableWidget, QStringList strContentList)
{
    int iColumnCount = pTableWidget->columnCount();
    int iContentListCount = strContentList.count();
    if(iContentListCount < 1 || iContentListCount != iColumnCount)
    {// 插入数据不正确，不进行插入操作
        return false;
    }
    // 创建行
    int iRow = pTableWidget->rowCount();
    pTableWidget->insertRow(iRow);

    QCheckBox *pCheckBox = new QCheckBox;
//    pCheckBox->setFixedSize(21, 21);
    pCheckBox->setChecked(false);
//    pCheckBox->setStyleSheet("QCheckBox::indicator {width: 50px; height: 50px;}");
    //
    QWidget *pCheckWidget = new QWidget;
    QHBoxLayout *pCheckLayout = new QHBoxLayout;
    pCheckLayout->setMargin(0);
    pCheckLayout->addSpacing(3);
    pCheckLayout->addWidget(pCheckBox, 0, Qt::AlignHCenter);
    pCheckWidget->setLayout(pCheckLayout);
    pTableWidget->setCellWidget(iRow, 0, (QWidget*)pCheckWidget);
    //
    for(int i = 1; i != iColumnCount; ++i)
    {
        if(!InsertOneItem(pTableWidget, iRow, i, strContentList.at(i)))
        {
            return false;
        }
    }
    return true;
}
bool InsertOneLineTop(QTableWidget *pTableWidget, QStringList strContentList, int iRow, int iColumnCount)
{

    // 创建行
  //  int iRow = pTableWidget->rowCount();
//    pTableWidget->insertRow(0);
    //
    for(int i = 0; i != iColumnCount; ++i)
    {
        QTableWidgetItem *pItem = new QTableWidgetItem;
        pItem->setText(strContentList.at(i));
        pTableWidget->setItem(iRow, i, pItem);
    }

    return true;
}
bool InsertOneColumn(QTableWidget *pTableWidget, QStringList strContentList)
{
    int iRowCount = pTableWidget->rowCount();
    int iContentListCount = strContentList.count();
    if(iContentListCount < 1 || iContentListCount != iRowCount)
    {// 插入数据不正确，不进行插入操作
        return false;
    }
    // 创建列
    int iColumn = pTableWidget->columnCount();
    pTableWidget->insertColumn(iColumn);
    //
    for(int i = 0; i != iRowCount; ++i)
    {
        if(!InsertOneItem(pTableWidget, i, iColumn, strContentList.at(i)))
        {
            return false;
        }
    }
    return true;
}
/**
  * @brief 向TableWidget某行某列添加Item
  * @param iRow：所在行
  * @param iColumn：所在列
  * @param strContent：Item显示的内容
  * @return true：添加成功；false：添加失败
  */
bool InsertOneItem(QTableWidget *pTableWidget, int iRow, int iColumn, QString strContent)
{

    int iColumnCount = pTableWidget->columnCount();
    int iRowCount = pTableWidget->rowCount();
    if(iColumn < iColumnCount && iRow < iRowCount)
    {
        QTableWidgetItem *pItem = new QTableWidgetItem;
        pItem->setText(strContent);
        pItem->setTextAlignment(Qt::AlignCenter);
        pTableWidget->setItem(iRow, iColumn, pItem);
        return true;
    }
    else
    {
        return false;
    }

}
/**
  * @brief 打印报告
  * @param strHtml：html格式打印
  * @return
  */
bool PrintToPage(QString strHtml)
{


    return false;
}
/**
  * @brief 保存报告PDF
  * @param strHtml: 待保存的数据流
  * @param pWidget: 保存对话框父类
  * @return
  */
bool PrintToPdf(QString strHtml, QWidget *pWidget)
{

    return false;
}

CCustomTabStyle::CCustomTabStyle()
    :QProxyStyle()
{

}

CCustomTabStyle::~CCustomTabStyle()
{

}

QSize CCustomTabStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
            if (type == QStyle::CT_TabBarTab) {
                s.transpose();
                s.rwidth() = 132; // 设置每个tabBar中item的大小
                s.rheight() = 85;
            }
            return s;
}

void CCustomTabStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel)
    {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
        {
            QRect allRect = tab->rect;

            if (tab->state & QStyle::State_Selected)
            {
                //线性渐变
                QLinearGradient linearGradient(0, 0, allRect.width(), 0);
                //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
                //painter.setPen(Qt::NoPen);
                linearGradient.setColorAt(0.0,0x1D80FF);
                linearGradient.setColorAt(1.0,0x28C9FF);

                painter->save();
                painter->setPen(QColor(255, 255, 255, 0));
                painter->setBrush(QBrush(linearGradient));
                painter->drawRect(allRect);
                painter->restore();
            }
            else
            {
                painter->save();
                painter->setPen(0x193461);
                painter->setBrush(QBrush(0x193461));
                painter->drawRect(allRect);
                painter->restore();
            }
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            if (tab->state & QStyle::State_Selected)
            {
                painter->setPen(0xFFFFFF);
            }
            else
            {
                painter->setPen(0x818282);
            }
            painter->setFont(QFont("Source Han Sans CNMT", 5));

            painter->drawText(QRect(allRect.x(), allRect.y() + 25, allRect.width(), allRect.height() - 25 ), tab->text, option);
            painter->drawPixmap(QRect(allRect.x() + 48, allRect.y() + 15, 40, 33), tab->icon.pixmap(40, 33));
            return;
        }
    }
    if (element == CE_TabBarTab)
    {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

static unsigned short ccitt_table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

/**
     * @brief getCRC16  获取CRC16
     * @param data  计算的数据
     * @param len  数据的长度
     * @param oldCRC16  上一个CRC16的值，用于循环计算大文件的CRC16。第一个数据的CRC16则传入0x0。
     * @return
     */
unsigned short GetCRC16(const char *pData, unsigned long ulLen, unsigned long ulOldCRC16)
{
    unsigned short crc16 = ulOldCRC16;

    while (ulLen-- > 0)
        crc16 = ccitt_table[(crc16 >> 8 ^ *pData++) & 0xff] ^ (crc16 << 8);
    return crc16;
}


void RemoveFile(QString strFilePath)
{
    if(strFilePath == "")
    {
        return;
    }
    qDebug() << "remove files " << strFilePath;
    QFile qFileTemp(strFilePath);
    if(qFileTemp.exists())
    {
        qFileTemp.remove();
    }
}
bool WriteJsonMap(QString strConfigFileName,
                                QString strParamsType,
                                QMap<QString,QVariant> qParamsMap)
{
    QFile qConfigfile(strConfigFileName);
        if(!qConfigfile.open(QIODevice::ReadWrite))
        {
            qDebug() << "Cannot open file for writing: ";
            return false;
        }

        QByteArray qJsonByteArray = qConfigfile.readAll();
        QString strFile = QString::fromLocal8Bit(qJsonByteArray.data());
         /*配置文件为空，直接按json格式写入*/
        if(qJsonByteArray.isEmpty())
        {
            QVariantMap qConfigureVariantMap;

            QMap<QString,QVariant> qConfiguretMap;
            QMap<QString,QVariant>::const_iterator qParamsMapIter;
            for (qParamsMapIter = qParamsMap.constBegin(); qParamsMapIter != qParamsMap.constEnd(); ++qParamsMapIter)
            {
                qConfiguretMap.insert(qParamsMapIter.key(),qParamsMapIter.value());
            }

            QVariant qConfiguretQVariant = static_cast <QVariant> (qConfiguretMap);

            qConfigureVariantMap.insert(strParamsType,qConfiguretQVariant);

            // 转化为 JSON 文档
            QJsonDocument qJsonDoucment = QJsonDocument::fromVariant(static_cast <QVariant>(qConfigureVariantMap));

            QByteArray qJosnByteArray = qJsonDoucment.toJson(QJsonDocument::Compact);
            QString strJson(qJosnByteArray);

            QTextStream qTextStreamOut(&qConfigfile);
            //清空文件
            qConfigfile.resize(0);
            //写入配置文件
            qTextStreamOut << strJson;
        }
        else
        {
            //配置文件不为空
            QJsonParseError sJsonError;
            // 转化为 JSON 文档
            QJsonDocument qJsonDoucment = QJsonDocument::fromJson(strFile.toStdString().data(), &sJsonError);
            if (!qJsonDoucment.isNull() && (sJsonError.error == QJsonParseError::NoError))
            {  // 解析未发生错误
                if (qJsonDoucment.isObject())
                { // JSON 文档为对象
                    QJsonObject qJosnObject = qJsonDoucment.object();  // 转化为对象
                    QVariantMap qConfigureVariantMap = qJosnObject.toVariantMap(); // json文件全部数据
                    QVariant qParamsTypeParamsVariant;
                    QMap<QString,QVariant> qParamsTypeParamsMap;     //存放新的参数
                    if(qConfigureVariantMap.contains(strParamsType)) //存在该配置项
                    {
                        //读出原配置项内容,不存在为空
                        qParamsTypeParamsVariant = qConfigureVariantMap.value(strParamsType);
                        qParamsTypeParamsMap = qParamsTypeParamsVariant.toMap();
                    }

                    QMap<QString,QVariant>::const_iterator qParamsMapIter;
                    for (qParamsMapIter = qParamsMap.constBegin(); qParamsMapIter != qParamsMap.constEnd(); ++qParamsMapIter)
                    {
                        //写入新内容，原来没有就插入，原来存在就覆盖
                        qParamsTypeParamsMap.insert(qParamsMapIter.key(),qParamsMapIter.value());
                    }

                    QVariant qConfiguretQVariant = static_cast <QVariant>(qParamsTypeParamsMap);
                    //重新插入QVariantMap
                    qConfigureVariantMap.insert(strParamsType,qConfiguretQVariant);
                    // 转化为 JSON 文档
                    qJsonDoucment = QJsonDocument::fromVariant(static_cast <QVariant>(qConfigureVariantMap));
                    QByteArray qJosnByteArray = qJsonDoucment.toJson(QJsonDocument::Compact);

                    QString strJson(qJosnByteArray);

                    QTextStream qTextStreamOut(&qConfigfile);
                    //清空文件
                    qConfigfile.resize(0);
                    //写入配置文件
                    qTextStreamOut << strJson;

                }
            }
        }
        qConfigfile.flush();
        qConfigfile.close();
        return true;
}

bool ReadJsonMap(QString strConfigFileName, QString strParamsType, QMap<QString, QVariant> *pParamsMap)
{
    QFile qConfigfile(strConfigFileName);
        if(!qConfigfile.open(QIODevice::ReadWrite))
        {
            return false;
        }
        QByteArray qJosnByteArray = qConfigfile.readAll();
        QString strFile = QString::fromLocal8Bit(qJosnByteArray.data());
        QJsonParseError qJsonError;
        QJsonDocument qJosnDoucment = QJsonDocument::fromJson(strFile.toStdString().data(), &qJsonError);  // 转化为 JSON 文档
        if (!qJosnDoucment.isNull() && (qJsonError.error == QJsonParseError::NoError))
        {  // 解析未发生错误
            if (qJosnDoucment.isObject())
            { // JSON 文档为对象
                QJsonObject qJosnObject = qJosnDoucment.object();  // 转化为对象
                if (qJosnObject.contains(strParamsType))
                {  // 包含指定的 key
                    // 获取指定 key 对应的 value
                    QMap<QString, QVariant> qJsonValueMap = qJosnObject.value(strParamsType).toVariant().toMap();
                    if (qJsonValueMap.isEmpty() == false)
                    {
                        QMap<QString,QVariant>::const_iterator ParamsMapIter;
                        for (ParamsMapIter = qJsonValueMap.constBegin(); ParamsMapIter != qJsonValueMap.constEnd();
                             ++ParamsMapIter)
                        {
                            //插入QMap
                            pParamsMap->insert(ParamsMapIter.key(),ParamsMapIter.value());
                        }
                        qConfigfile.close();
                        return true;
                    }
                }
            }
        }

        qConfigfile.close();
        return false;
}




void SetSystemDataTime(QDateTime qDateTime)
{
        QString str= "date -s \"2019-01-26 10:15:55\"";
        system(str.toLatin1().data());
        //强制写入到CMOS
        system("hwclock -w");
}

/*方法1*/
bool MkDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
    //只创建一级子目录，即必须保证上级目录存在
        QProcess ::execute("mkdir " + fullPath);
       return true;
    }
}
void WaitSleep(qint32 iMsec)
{
    QTime qOldTime = QTime::currentTime();
    qint16 iSeconds = 0;
    while(1)
    {
        iSeconds = qOldTime.msecsTo(QTime::currentTime());
        if(iSeconds > iMsec)
        {
            break;
        }
        QApplication::processEvents();
    }
}

void TableToPrePage(QTableWidget *pTableWidget, int iOnePageNumber)
{
    int maxValue = pTableWidget->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    int iCurScroller = pTableWidget->verticalScrollBar()->value();
    if(iCurScroller>0)
        pTableWidget->verticalScrollBar()->setSliderPosition(iCurScroller-iOnePageNumber);
    else
        pTableWidget->verticalScrollBar()->setSliderPosition(maxValue);

}

void TableToNextPage(QTableWidget *pTableWidget, int iOnePageNumber)
{
    int maxValue = pTableWidget->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    int iCurScroller = pTableWidget->verticalScrollBar()->value(); //获得当前scroller值
    if(iCurScroller<maxValue)
        pTableWidget->verticalScrollBar()->setSliderPosition(iOnePageNumber+iCurScroller);
    else
        pTableWidget->verticalScrollBar()->setSliderPosition(0);

}
void TableToLeftPage(QTableWidget *pTableWidget, int iOnePageNumber)
{
    int maxValue = pTableWidget->horizontalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    int iCurScroller = pTableWidget->horizontalScrollBar()->value();
    if(iCurScroller>0)
        pTableWidget->horizontalScrollBar()->setSliderPosition(iCurScroller-iOnePageNumber);
    else
        pTableWidget->horizontalScrollBar()->setSliderPosition(maxValue);
}


void TableToRightPage(QTableWidget *pTableWidget, int iOnePageNumber)
{
    int maxValue = pTableWidget->horizontalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    int iCurScroller = pTableWidget->horizontalScrollBar()->value(); //获得当前scroller值
    if(iCurScroller<maxValue)
        pTableWidget->horizontalScrollBar()->setSliderPosition(iOnePageNumber+iCurScroller);
    else
        pTableWidget->horizontalScrollBar()->setSliderPosition(0);
}

bool GetCurrentSelectRows(QTableWidget *pTableWidget, QVector<int> &qSelectVector)
{

    QList<QTableWidgetItem* > qItemsList = pTableWidget->selectedItems();
    int iItemCount = qItemsList.count();
    if(iItemCount <= 0)
    {
        return false;
    }
    int iItemRow;
    for(int i=0; i < iItemCount; ++i)
    {
        //获取选中的行
        iItemRow = pTableWidget->row(qItemsList.at(i));
        if(!qSelectVector.contains(iItemRow))
        {
            qSelectVector.append(iItemRow);
        }

    }
    qSort(qSelectVector.begin(),qSelectVector.end());//从小到大

    return  true;
}

void DeleteTabelSelctRows(QTableWidget *pTableWidget)
{
    QVector<int> qSelectVector;
    GetCurrentSelectRows(pTableWidget, qSelectVector);
    // 删除
    int qSelectVectorCount = qSelectVector.count();
    QTableWidgetItem *pIDItem  = NULL;
    for(int iPos = 0; iPos < qSelectVectorCount; iPos++)
    {
        int iRow = qSelectVector.at(qSelectVectorCount - iPos - 1);
        pIDItem = pTableWidget->item(iRow, 0);
        pTableWidget->removeRow(iRow);
    }
}


/**
 * @brief CopyFileDir
 * @param kstrSrcDir
 * @param kstrDestDir
 * @param bCoverFileIfExist
 * @return
 */
bool CopyFileDir(const QString &kstrSrcDir, const QString &kstrDestDir, bool bCoverFileIfExist)
{
    QDir qSourceDir(kstrSrcDir);
    QDir qTargetDir(kstrDestDir);
    if(!qTargetDir.exists())
    {    /**< 如果目标目录不存在，则进行创建 */
        if(!qTargetDir.mkdir(qTargetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = qSourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir())
        {    /**< 当为目录时，递归的进行copy */
            if(!CopyFileDir(fileInfo.filePath(),
                qTargetDir.filePath(fileInfo.fileName()),
                bCoverFileIfExist))
                return false;
        }
        else
        {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(bCoverFileIfExist && qTargetDir.exists(fileInfo.fileName()))
            {
                qTargetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                qTargetDir.filePath(fileInfo.fileName())))
            {
                    return false;
            }
        }
    }
    return true;
}



