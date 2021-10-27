#ifndef VEHICLEDISPLAYADAPTOR_H
#define VEHICLEDISPLAYADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusArgument>
#include <QTimer>


//添加接口以及属性到dbus，可通过d-feet查看
class VehicleMediaControlAdaptor :public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.ise.proxy.media")
    Q_CLASSINFO("D-Bus Introspection", ""
    "  <interface name=\"com.ise.proxy.media\">\n"
    "    <method name=\"RequstAllData\">\n"
    "      <arg direction=\"out\" type=\"v\" name=\"MimeInfo\"/>\n"
    "    </method>\n"
    "    <signal name=\"SigPlay\">\n"
    "      <arg direction=\"out\" type=\"s\" name=\"uri\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigPause\"/>\n"
    "    <signal name=\"SigResume\"/>\n"
    "    <signal name=\"SigNext\">\n"
    "      <arg direction=\"out\" type=\"s\" name=\"uri\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigPrevious\">\n"
    "      <arg direction=\"out\" type=\"s\" name=\"uri\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigMuteChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"mute\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigVolumeChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"volume\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigPlayModeChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"mode\"/>\n"
    "    </signal>\n"
    "  </interface>\n"
    "")

signals:
    Q_SIGNAL void SigPlay(QString);
    Q_SIGNAL void SigPause();
    Q_SIGNAL void SigResume();
    Q_SIGNAL void SigNext(QString);
    Q_SIGNAL void SigPrevious(QString);
    Q_SIGNAL void SigMuteChanged(bool);
    Q_SIGNAL void SigVolumeChanged(int);
    Q_SIGNAL void SigPlayModeChanged(int);
public slots:
    Q_INVOKABLE void slotSetUri(const QString&,int type);
    Q_INVOKABLE void slotSetMute(bool);
    Q_INVOKABLE void slotSetVolume(int);
    Q_INVOKABLE void slotPlayMode(int);
    Q_INVOKABLE QDBusVariant RequstAllData();
public:
    VehicleMediaControlAdaptor(QObject *parent=nullptr);
    ~VehicleMediaControlAdaptor(){}
private:
    bool    m_mute;
    int     m_volume;
    int     m_playMode;
    int     m_playbackStatus;
    QString m_playUri;
};

#endif // VEHICLEDISPLAYADAPTOR_H
