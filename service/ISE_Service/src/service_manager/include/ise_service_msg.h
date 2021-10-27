#ifndef ISE_SERVICE_MSG_H
#define ISE_SERVICE_MSG_H

#include "ise_common.h"
#include <QDBusArgument>
#include <QDBusMetaType>
#include <QPoint>
#include <QVector>
#include <QVariant>

namespace ise_service
{
	enum IseServiceID
	{
		ISE_SERVICE_ID_UNKNOWN = -1,
		ISE_CAN_SERVICE_ID,
		ISE_DBUS_SERVICE_ID,
		ISE_UDP_SERVICE_ID,
		ISE_USB_SERVICE_ID,
		ISE_UPDATE_SERVICE_ID,
		ISE_MEDIA_SERVICE_ID,
		ISE_WEB_SCRIBE_SERVICE_ID,
		ISE_LOG_SERVICE_ID,
		ISE_MAP_SERVICE_ID,
		AMP_SRVICE_ID_MAX
	};
	
    enum IseMessageID
    {
        MESSAGE_ID_UNKNOWN = -1,
        MESSAGE_ID_SOC = 10,           //vehicle info from can
        MESSAGE_ID_BATTERY_TEMPERATURE,
        MESSAGE_ID_EPS_FAULT,
        MESSAGE_ID_EHT_FAULT,
        MESSAGE_ID_OPERATE_MODE,
        MESSAGE_ID_GEAR,
        MESSAGE_ID_EBP,
        MESSAGE_ID_WHOLE_FAULT,
        MESSAGE_ID_DOOR_OPEN_STATE,
        MESSAGE_ID_TIRE_PRESSURE,
        MESSAGE_ID_DIPPED_BEAM,
        MESSAGE_ID_REAR_FOG_LAMP,
        MESSAGE_ID_SIGNAL_LEFT_LAMP,
        MESSAGE_ID_SIGNAL_RIGHT_LAMP,
        MESSAGE_ID_EMERGENCY_FLASHERS,
        MESSAGE_ID_HIGH_BEAM,

        MESSAGE_ID_BLOWING_RATE = 30, //air conditioner info from can
        MESSAGE_ID_VENTILATE_MODE,
        MESSAGE_ID_COOL_AIR_STATE,
        MESSAGE_ID_HEAT_AIR_STATE,
        MESSAGE_ID_AIR_CONDITIONER_SWITCH,
        MESSAGE_ID_OUTDOOR_TEMPERATURE,

        MESSAGE_ID_MAP_INFO = 40, //map info from can
        MESSAGE_ID_RT_POSITION,
        MESSAGE_ID_REACH_STATION,

        MESSAGE_ID_ADV_TEMPERATURE = 50,
        MESSAGE_ID_ADV_NEWS,

        MESSAGE_ID_ATMOSPHERE_LAMP_SET = 60, //all set to can
        MESSAGE_ID_TOP_LIGHT_SET,
        MESSAGE_ID_POWER_SEATS_SET,
        MESSAGE_ID_BLOWING_RATE_SET,
        MESSAGE_ID_VENTILATE_MODE_SET,
        MESSAGE_ID_COOL_AIR_STATE_SET,
        MESSAGE_ID_HEAT_AIR_STATE_SET,
        MESSAGE_ID_AIR_CONDITIONER_SWITCH_SET,
        MESSAGE_ID_OUTDOOR_TEMPERATURE_SET,
        MESSAGE_ID_DIPPED_BEAM_SET,
        MESSAGE_ID_HIGH_BEAM_SET,
        MESSAGE_ID_REAR_FOG_LAMP_SET,
        MESSAGE_ID_SIGNAL_LEFT_LAMP_SET,
        MESSAGE_ID_SIGNAL_RIGHT_LAMP_SET,
        MESSAGE_ID_EMERGENCY_FLASHERS_SET,
        MESSAGE_ID_HORN_SET,

        MESSAGE_ID_STATION_MANAGER = 80,    //map set form pad
        NESSAFE_ID_ROUTE_MANAGER,

        MESSAGE_ID_GET_PLAYLIST = 90,       //playback set to host
        MESSAGE_ID_PLAYBACK_CONTROL,

        MESSAGE_ID_VOLUME_SYSTEM_SET = 100, //volume setting from pad
        MESSAGE_ID_VOLUME_MULTI_MEDIA,
    };

    struct ISE_CAN_Message : public ISE_MSG_HEAD
    {
        ISE_UINT8             reserved;

    public:
        ISE_CAN_Message(IseMessageID msgid) : ISE_MSG_HEAD(msgid, sizeof(*this))
        {

        }

        ~ISE_CAN_Message(){}
    };

}

#endif  /*__ISE_SERVICE_MSG_H__*/
