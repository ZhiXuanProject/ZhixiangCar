#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTimer>
#include <QList>


class AdvertisementInfo : public QObject
{
    Q_OBJECT
public:
    explicit AdvertisementInfo(QObject *parent = nullptr);
    ~AdvertisementInfo();

private:
    void parseWeatherUrl(const QString& content);
    void parseNewsUrl(const QString& content);

    void clean();
signals:
    void sigParseWeatherFinish(QString& weather);
    void sigParseTmpFinish(QString& Tmp);
    void sigParseNewsFinish(QList<QString>& news);

private slots:
    void slotReplyWeatherfinished(QNetworkReply *reply);
    void slotReplyNewsFinished(QNetworkReply *reply);
    void slotWeather(QString& weather);
    void slotTmp(QString& tmp);
    void slotNews(QList<QString>& news);
    void slotTimerOut();

private:
    QNetworkAccessManager *m_pWeatherAccess;
    QNetworkAccessManager *m_pNewsAccess;
    QString m_strWeatherUrl;
    QString m_strNewsUrl;
    QString m_strWeather;
    QString m_strTmp;
    QList<QString> m_newsList;
    QTimer *m_pTimer;
};

#endif // NETWORK_H
