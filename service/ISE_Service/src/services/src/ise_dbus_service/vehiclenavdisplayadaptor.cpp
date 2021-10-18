#include "vehiclenavdisplayadaptor.h"

#include <QDebug>
#include <QTime>
#include <qmimetype.h>
#include <QVariant>
#include <QDBusMetaType>
#include <QDBusArgument>

VehicleNavDisplayAdaptor::VehicleNavDisplayAdaptor(QObject *parent):QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(false);
}


QDBusVariant VehicleNavDisplayAdaptor::GetNavMap()
{
//    QDBusArgument argument;
//    //argument<<m_navMap;

//    QVariant var;
//    var.setValue(argument);

    QDBusVariant  dbusvar;
//    dbusvar.setVariant(var);

    return dbusvar;
}

void VehicleNavDisplayAdaptor::SetNavMap(const QString &path, const QVector<QPoint> &vec)
{
//    m_navMap.vNavMap = path;
//    m_navMap.vStations = std::move(vec);
}
