#include "vehiclebusproxy.h"
#include "./adaptor/vehicleinformationadaptor.h"
#include "./adaptor/vehiclemediacontroladaptor.h"
#include "./adaptor/vehiclenavdisplayadaptor.h"

#include <QDebug>

const QString serviceName = "com.vehicle.proxy";
const QString servicePath = "/com/vehicle/proxy";

VehicleBusService::VehicleBusService(QObject* parent ):QObject (parent),QDBusContext(),
                                                    m_vInfoAdaptor(new VehicleInfoAdaptor(this)),
                                                    m_vDspAdaptor(new VehicleMediaControlAdaptor(this)),
                                                    m_vNavDspAdaptor(new VehicleNavDisplayAdaptor(this))

{

}

VehicleBusService::~VehicleBusService()
{
    if(QDBusConnection::sessionBus().isConnected())
    {
        qDebug()<<__FUNCTION__<<"unregist service.";
        QDBusConnection::sessionBus().unregisterObject(servicePath);
        QDBusConnection::sessionBus().unregisterService(serviceName);
    }
}

VehicleBusService* VehicleBusService::getInstance()
{
    static VehicleBusService tBusService(nullptr);
    return &tBusService;
}

void VehicleBusService::initBus()
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

void VehicleBusService::onMessage(QString)
{

}

