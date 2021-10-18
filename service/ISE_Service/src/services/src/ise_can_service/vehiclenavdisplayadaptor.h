#ifndef VEHICLENAVDISPLAYADAPTOR_H
#define VEHICLENAVDISPLAYADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusArgument>

#include "common.h"

//添加接口以及属性到dbus，可通过d-feet查看
class VehicleNavDisplayAdaptor :public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vehicle.proxy.navigation")
    Q_CLASSINFO("D-Bus Introspection", ""
    "  <interface name=\"com.vehicle.proxy.navigation\">\n"
    "    <method name=\"GetNavMap\">\n"
    "      <arg direction=\"out\" type=\"v\" name=\"mapinfo\"/>\n"
    "    </method>\n"
    "    <signal name=\"SigPositionChanged\">\n"
    "      <arg direction=\"out\" type=\"v\" name=\"position\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigMapChanged\">\n"
    "      <arg direction=\"out\" type=\"v\" name=\"mapinfo\"/>\n"
    "    </signal>\n"
    "  </interface>\n"
    "")

signals:
    Q_SIGNAL void SigPositionChanged(QDBusVariant);
    Q_SIGNAL void SigMapChanged(QDBusVariant);
public slots:
    Q_INVOKABLE QDBusVariant GetNavMap();
    Q_INVOKABLE void SetNavMap(const QString& path,const QVector<QPoint>& vec);
public:
    VehicleNavDisplayAdaptor(QObject *parent=nullptr);
    ~VehicleNavDisplayAdaptor(){}
private:
    VehicleNavPosition m_navPos;
    VehicleNavMap     m_navMap;
};

#endif // VEHICLENAVDISPLAYADAPTOR_H
