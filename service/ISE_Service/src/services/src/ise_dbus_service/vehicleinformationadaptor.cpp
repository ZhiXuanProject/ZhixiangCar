#include "vehicleinformationadaptor.h"
#include "ise_dbus_msg.h"

#include <QDebug>
#include <QTime>

VehicleInfoAdaptor::VehicleInfoAdaptor(QObject *parent):QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(false);
}

QDBusVariant VehicleInfoAdaptor::RequstAllData()
{
    QDBusVariant var;

    return var;
}
