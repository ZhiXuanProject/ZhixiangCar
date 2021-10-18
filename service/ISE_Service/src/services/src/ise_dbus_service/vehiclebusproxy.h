#ifndef VEHICLEBUSPROXY_H
#define VEHICLEBUSPROXY_H

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusVariant>


class VehicleInfoAdaptor;
class VehicleMediaControlAdaptor;
class VehicleNavDisplayAdaptor;
class VehicleDbusProxy: public QObject,protected QDBusContext
{
    Q_OBJECT
public:
    static VehicleDbusProxy* getInstance();
    void initBus();
public slots:
    void onMessage(QString);
private:
    VehicleDbusProxy(QObject* p = nullptr);
    ~VehicleDbusProxy();
private:
    VehicleInfoAdaptor *m_vInfoAdaptor = nullptr;
    VehicleMediaControlAdaptor *m_vDspAdaptor = nullptr;
    VehicleNavDisplayAdaptor *m_vNavDspAdaptor = nullptr;

    friend VehicleInfoAdaptor;
    friend VehicleMediaControlAdaptor;
    friend VehicleNavDisplayAdaptor;
};

#endif // VEHICLEBUSPROXY_H
