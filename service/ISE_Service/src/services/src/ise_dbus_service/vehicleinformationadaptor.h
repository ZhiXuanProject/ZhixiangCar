#ifndef VEHICLEINFOADAPTOR_H
#define VEHICLEINFOADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusArgument>

//添加接口以及属性到dbus，可通过d-feet查看
class VehicleInfoAdaptor :public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.ise.proxy.vehicleinfo")
    Q_CLASSINFO("D-Bus Introspection", ""
    "  <interface name=\"com.ise.proxy.vehicleinfo\">\n"
    "    <method name=\"RequstAllData\">\n"
    "      <arg direction=\"out\" type=\"v\" name=\"data\"/>\n"
    "    </method>\n"
    "    <signal name=\"SigSpeedChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"speed\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigSocChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"soc\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigBatteryTemperatureChanged\">\n"
    "      <arg direction=\"out\" type=\"d\" name=\"temperature\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigEpsFaultChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"fault\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigEhtFaultChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"fault\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigVehicleModeChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"mode\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigHighBeamChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"beam\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigCornerLampChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"lamp\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigGearChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"gear\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigEpbChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"epb\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigVehicleFaultChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"fault\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigDoorStateChanged\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"state\"/>\n"
    "    </signal>\n"
    "    <signal name=\"SigTirePressureChanged\">\n"
    "      <arg direction=\"out\" type=\"i\" name=\"pressure\"/>\n"
    "    </signal>\n"
    "  </interface>\n"
    "")

signals:
    Q_SIGNAL void SigSpeedChanged(int);
    Q_SIGNAL void SigSocChanged(int);
    Q_SIGNAL void SigBatteryTemperatureChanged(double);
    Q_SIGNAL void SigEpsFaultChanged(bool);
    Q_SIGNAL void SigEhtFaultChanged(bool);
    Q_SIGNAL void SigVehicleModeChanged(int);
    Q_SIGNAL void SigHighBeamChanged(bool);
    Q_SIGNAL void SigCornerLampChanged(int);
    Q_SIGNAL void SigEpbChanged(bool);
    Q_SIGNAL void SigVehicleFaultChanged(bool);
    Q_SIGNAL void SigDoorStateChanged(bool);
    Q_SIGNAL void SigTirePressureChanged(int);
public slots:
    Q_INVOKABLE QDBusVariant RequstAllData();
public:
    VehicleInfoAdaptor(QObject *parent=nullptr);
    ~VehicleInfoAdaptor(){}
private:
};

#endif // VEHICLEINFOADAPTOR_H
