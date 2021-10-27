#include "advertisementinfo.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTextCodec>

using namespace ise_service;
AdvertisementInfo::AdvertisementInfo(QObject *parent) : QObject(parent)
{
    //新建QNetworkAccessManager对象
    m_pWeatherAccess = new QNetworkAccessManager(this);
    m_pNewsAccess = new QNetworkAccessManager(this);
    m_pTimer = new QTimer(this);

    //关联信号和槽
    connect(m_pWeatherAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyWeatherfinished(QNetworkReply*)));
    connect(m_pNewsAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyNewsFinished(QNetworkReply*)));
    connect(this, SIGNAL(sigParseWeatherFinish(QString&)), this, SLOT(slotWeather(QString&)));
    connect(this, SIGNAL(sigParseTmpFinish(QString&)), this, SLOT(slotTmp(QString&)));
    connect(this, SIGNAL(sigParseNewsFinish(QList<QString>&)), this, SLOT(slotNews(QList<QString>&)));
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotTimerOut()));

    //发送请求
    m_pWeatherAccess->get(QNetworkRequest(QUrl("http://apis.juhe.cn/simpleWeather/query?city=%E5%8C%97%E4%BA%AC&key=49c503cb6a693b6b99e716c53c9fe4ca")));
    m_pNewsAccess->get(QNetworkRequest(QUrl("http://v.juhe.cn/toutiao/index?type=top&key=c0b0617759de7738766b91ffeebbd5dc")));
    m_pTimer->start(30*60*1000);
}

AdvertisementInfo::~AdvertisementInfo()
{

}

void AdvertisementInfo::parseWeatherUrl(const QString &content)
{
    qDebug()<<"NetWork::parseWeatherUrl";

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    if(jsonObject.contains(QStringLiteral("result")))
    {
        QJsonValue jsonValueList = jsonObject.value(QStringLiteral("result"));
        QJsonObject item = jsonValueList.toObject();
        if(item.contains(QStringLiteral("realtime")))
        {
            QJsonValue jsonValueList1 = item.value(QStringLiteral("realtime"));
            QJsonObject item1 = jsonValueList1.toObject();
            //qDebug()<<"item1[temperature]=="<<item1["temperature"].toString();
            //qDebug()<<"item1[info]=="<<item1["info"].toString();
            m_strWeather = item1["info"].toString();
            m_strTmp = item1["temperature"].toString();
            emit sigParseWeatherFinish(m_strWeather);
            emit sigParseTmpFinish(m_strTmp);
//            ISE_MSG_HEAD msghead;
//            ISE_UINT16 serviceid;
//            ExtSendIseServiceMsg(serviceid, &msghead);
        }
    }
}

void AdvertisementInfo::parseNewsUrl(const QString &content)
{
    qDebug()<<"NetWork::parseNewsUrl";

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    if(jsonObject.contains(QStringLiteral("result")))
    {
        QJsonValue jsonValueList = jsonObject.value(QStringLiteral("result"));
        QJsonObject item = jsonValueList.toObject();
        QJsonValue arrayValue = item.value(QStringLiteral("data"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();
            for(int i=0; i<array.size(); i++)
            {
                QJsonValue newsArray = array.at(i);
                QJsonObject itemObject = newsArray.toObject();

                //qDebug()<<"itemObject[title]="<<itemObject["title"].toString();
                m_newsList.append(itemObject["title"].toString());
            }
        }
    }

    //emit sigParseNewsFinish(m_newsList);
//    ISE_MSG_HEAD msghead;
//    msghead.msg_id = MESSAGE_ID_ADV_NEWS;
//    ExtSendIseServiceMsg(ISE_DBUS_SERVICE_ID, &msghead);
}

void AdvertisementInfo::clean()
{
    m_newsList.clear();
    m_strTmp = "";
    m_strWeather = "";
}

void AdvertisementInfo::slotReplyWeatherfinished(QNetworkReply *reply)
{
    qDebug()<<"NetWork::slotReplyWeatherfinished";

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //使用utf8编码, 这样可以显示中文
    m_strWeatherUrl = codec->toUnicode(reply->readAll());
    reply->deleteLater(); //最后要释放replay对象
    //qDebug()<<m_strWeatherUrl;
    parseWeatherUrl(m_strWeatherUrl);
}

void AdvertisementInfo::slotReplyNewsFinished(QNetworkReply *reply)
{
    qDebug()<<"NetWork::slotReplyNewsFinished";

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //使用utf8编码, 这样可以显示中文
    m_strNewsUrl = codec->toUnicode(reply->readAll());
    reply->deleteLater(); //最后要释放replay对象
    parseNewsUrl(m_strNewsUrl);
}

void AdvertisementInfo::slotWeather(QString &weather)
{
    qDebug()<<"NetWork::slotWeather";
    qDebug()<<weather;
}

void AdvertisementInfo::slotTmp(QString &tmp)
{
    qDebug()<<"NetWork::slotTmp";
    qDebug()<<tmp;
}

void AdvertisementInfo::slotNews(QList<QString> &news)
{
    qDebug()<<"NetWork::slotNews";

    for(int i=0; i<news.size(); i++)
    {
        qDebug()<<"news:"<<news[i];
    }
}

void AdvertisementInfo::slotTimerOut()
{
    qDebug()<<"NetWork::slotTimerOut";
    //清除上一次的缓存数据
    clean();
    //发送请求
    m_pWeatherAccess->get(QNetworkRequest(QUrl("http://apis.juhe.cn/simpleWeather/query?city=%E5%8C%97%E4%BA%AC&key=49c503cb6a693b6b99e716c53c9fe4ca")));
    m_pNewsAccess->get(QNetworkRequest(QUrl("http://v.juhe.cn/toutiao/index?type=top&key=c0b0617759de7738766b91ffeebbd5dc")));
}
