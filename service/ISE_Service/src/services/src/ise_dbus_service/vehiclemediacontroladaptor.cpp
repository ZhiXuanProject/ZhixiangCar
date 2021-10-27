#include "vehiclemediacontroladaptor.h"
#include "ise_dbus_msg.h"

#include <QDebug>
#include <QTime>
#include <qmimetype.h>
#include <QVariant>
#include <QDBusMetaType>
#include <QDBusArgument>

using namespace ise_dbus_msg;
VehicleMediaControlAdaptor::VehicleMediaControlAdaptor(QObject *parent):QDBusAbstractAdaptor(parent),
                            m_mute(false),m_volume(0),m_playMode(0),m_playUri("")
{
    setAutoRelaySignals(false);
}

void VehicleMediaControlAdaptor::slotSetUri(const QString &path,int type)
{
    m_playUri = path;
    switch (type) {
    case ise_dbus_msg::PLAY:
        emit SigPlay(path);
        break;
    case ise_dbus_msg::NEXT:
        emit SigNext(path);
        break;
    case ise_dbus_msg::PREVIOUS:
        emit SigPrevious(path);
        break;
    default:
        return;
    }
}

void VehicleMediaControlAdaptor::slotSetMute(bool mute)
{
    m_mute = mute;
    emit SigMuteChanged(m_mute);
}

void VehicleMediaControlAdaptor::slotSetVolume(int vol)
{
    m_volume = vol;
    emit SigVolumeChanged(m_volume);
}

void VehicleMediaControlAdaptor::slotPlayMode(int mode)
{
    m_playMode = mode;
    emit SigPlayModeChanged(m_playMode);
}

QDBusVariant VehicleMediaControlAdaptor::RequstAllData()
{
    MeidaCtlInfo mineinfo;
    mineinfo.mute = m_mute;
    mineinfo.volume = m_volume;
    mineinfo.mode = m_playMode;
    mineinfo.status = m_playbackStatus;
    mineinfo.currentPath = m_playUri;

    QDBusArgument argument;
    argument<<mineinfo;

    QVariant var;
    var.setValue(argument);

    QDBusVariant  dbusvar;
    dbusvar.setVariant(var);

    return dbusvar;
}
