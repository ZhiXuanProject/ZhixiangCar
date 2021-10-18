#include "vehiclebusproxy.h"
#include "vehicleinformationadaptor.h"
#include "vehiclemediacontroladaptor.h"
#include "vehiclenavdisplayadaptor.h"

#include <QDebug>

const QString serviceName = "com.ise.proxy";
const QString servicePath = "/com/ise/proxy";

VehicleDbusProxy::VehicleDbusProxy(QObject* parent ):QObject (parent),QDBusContext(),
                                                    m_vInfoAdaptor(new VehicleInfoAdaptor(this)),
                                                    m_vDspAdaptor(new VehicleMediaControlAdaptor(this)),
                                                    m_vNavDspAdaptor(new VehicleNavDisplayAdaptor(this))
{

}

VehicleDbusProxy::~VehicleDbusProxy()
{
    if(QDBusConnection::sessionBus().isConnected())
    {
        qDebug()<<__FUNCTION__<<"unregist service.";
        QDBusConnection::sessionBus().unregisterObject(servicePath);
        QDBusConnection::sessionBus().unregisterService(serviceName);
    }
}

VehicleDbusProxy* VehicleDbusProxy::getInstance()
{
    static VehicleDbusProxy tBusService(nullptr);
    return &tBusService;
}

void VehicleDbusProxy::initBus()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    //register object
    connection.registerObject(servicePath,this);
    //register service
    if(!connection.registerService(serviceName))
    {
        qCritical()<<__FUNCTION__<<"vehicle service connect failed!";
    }
}

void VehicleDbusProxy::onMessage(QString)
{

}

