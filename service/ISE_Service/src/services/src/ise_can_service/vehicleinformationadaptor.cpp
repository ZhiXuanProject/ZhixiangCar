#include "vehicleinformationadaptor.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

VehicleInfoAdaptor::VehicleInfoAdaptor(QObject *parent):QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(false);
}

QDBusVariant VehicleInfoAdaptor::RequstAllData()
{
    QDBusVariant var;

    return var;
}
