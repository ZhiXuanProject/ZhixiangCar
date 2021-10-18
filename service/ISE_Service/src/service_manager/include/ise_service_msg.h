#ifndef __ISE_SERVICE_MSG_H__
#define __ISE_SERVICE_MSG_H__

#include "ise_message_base.h"
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

        MESSAGE_ID_ATMOSPHERE_LAMP_SET = 50, //all set to can
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

        MESSAGE_ID_STATION_MANAGER = 70,    //map set form pad
        NESSAFE_ID_ROUTE_MANAGER,

        MESSAGE_ID_GET_PLAYLIST = 80,       //playback set to host
        MESSAGE_ID_PLAYBACK_CONTROL,

        MESSAGE_ID_VOLUME_SYSTEM_SET = 90, //volume setting from pad
        MESSAGE_ID_VOLUME_MULTI_MEDIA,
    };


    struct IseVehicleInfoStruct
    {
        int vSpeed; //车速 数字+单位
        int vSoc; //SOC 电池模型
        double vBatteryTemperature; //电池温度 数字+图标
        bool vEPSFault; //EPS故障
        bool vEhtFault;  //高压故障
        int  vWholeMode; //整车模式
        int  vGear; //档位
        bool vEpb; //EPB
        bool vWholeFault; //整车故障
        bool vDoorState;  //开门状态 动画
        int  vTirePressure; //胎压 数字+单位
        bool vDippedBeam;
        bool vRearFogLamp;
        bool vSignalLeftLamp;
        bool vSignalRightLamp;
        bool vEmergencyFlashers;
        bool vHighBeam; //远光灯

        friend QDBusArgument &operator <<(QDBusArgument &argument,const IseVehicleInfoStruct& info)
        {
            argument.beginStructure();
            argument<<info.vSpeed
                    <<info.vSoc
                    <<info.vBatteryTemperature
                    <<info.vEPSFault
                    <<info.vEhtFault
                    <<info.vWholeMode
                    <<info.vGear
                    <<info.vEpb
                    <<info.vWholeFault
                    <<info.vDoorState
                    <<info.vTirePressure
                    <<info.vDippedBeam
                    <<info.vRearFogLamp
                    <<info.vSignalLeftLamp
                    <<info.vSignalRightLamp
                    <<info.vEmergencyFlashers
                    <<info.vHighBeam;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,IseVehicleInfoStruct& info)
        {
            argument.beginStructure();
            argument>>info.vSpeed
                    >>info.vSoc
                    >>info.vBatteryTemperature
                    >>info.vEPSFault
                    >>info.vEhtFault
                    >>info.vWholeMode
                    >>info.vGear
                    >>info.vEpb
                    >>info.vWholeFault
                    >>info.vDoorState
                    >>info.vTirePressure
                    >>info.vDippedBeam
                    >>info.vRearFogLamp
                    >>info.vSignalLeftLamp
                    >>info.vSignalRightLamp
                    >>info.vEmergencyFlashers
                    >>info.vHighBeam;
            argument.endStructure();
            return argument;
        }
    };

    struct IseNavMap
    {
        QString vNavMap;
        QVector<QPoint> vStations;

        friend QDBusArgument &operator << (QDBusArgument &argument,const IseNavMap& map)
        {
            argument.beginStructure();
            argument<<map.vNavMap<<map.vStations;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,IseNavMap& map)
        {
            argument.beginStructure();
            argument>>map.vNavMap>>map.vStations;
            argument.endStructure();
            return argument;
        }
    };


    struct IseNavPosition
    {
        bool vReachStation;
        QPoint vCurrentPos;
        QPoint vStationPos;

        friend QDBusArgument &operator << (QDBusArgument &argument,const IseNavPosition& nav)
        {
            argument.beginStructure();
            argument<<nav.vCurrentPos<<nav.vReachStation<<nav.vStationPos;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,IseNavPosition& nav)
        {
            argument.beginStructure();
            argument>>nav.vCurrentPos>>nav.vReachStation>>nav.vStationPos;
            argument.endStructure();
            return argument;
        }
    };

    enum MeidaOperateType
    {
        NONE,
        PLAY,
        NEXT,
        PREVIOUS,
        MUTE,
        VOLUME,
        PLAYBACKMODE
    };

    struct IseMeidaCtlInfo
    {

        bool    mute;
        int     volume; //播放器音量，系统音
        int     mode;
        int     operate = NONE; //dbus不接受自定义枚举，使用int类型表示
        QString path;
        friend QDBusArgument &operator << (QDBusArgument &argument,const IseMeidaCtlInfo& info)
        {
            argument.beginStructure();
            argument<<info.mute<<info.volume<<info.mode<<info.path<<info.operate;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,IseMeidaCtlInfo& info)
        {
            argument.beginStructure();
            argument>>info.mute>>info.volume>>info.mode>>info.path>>info.operate;
            argument.endStructure();
            return argument;
        }
    };

    struct IseAirConditioner
    {
        int blowing_rate;
        int bentilate_mode;
        bool cool_air_state;
        bool heat_air_state;
        bool air_conditioner_switch;
        double outdoor_temperature;

        friend QDBusArgument &operator << (QDBusArgument &argument,const IseAirConditioner& air)
        {
            argument.beginStructure();
            argument<<air.blowing_rate
                    <<air.bentilate_mode
                    <<air.cool_air_state
                    <<air.heat_air_state
                    <<air.air_conditioner_switch
                    <<air.outdoor_temperature;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,IseAirConditioner& air)
        {
            argument.beginStructure();
            argument>>air.blowing_rate
                    >>air.bentilate_mode
                    >>air.cool_air_state
                    >>air.heat_air_state
                    >>air.air_conditioner_switch
                    >>air.outdoor_temperature;
            argument.endStructure();
            return argument;
        }
    };


    struct _ISE_ALIGN( 1 ) _ISE_PACKED ISE_CAN_COMMAND  : public ISE_MSG_HEAD
    {
        ISE_UINT8             reserved;

    public:
        ISE_CAN_COMMAND() : ISE_MSG_HEAD(ISE_CAN_SERVICE_ID, MESSAGE_ID_SOC, sizeof(*this))
        {
            /*DO NOTHING*/
        }
    };
}

Q_DECLARE_METATYPE(ise_service::IseVehicleInfoStruct)
Q_DECLARE_METATYPE(ise_service::IseNavMap)
Q_DECLARE_METATYPE(ise_service::IseNavPosition)
Q_DECLARE_METATYPE(ise_service::IseMeidaCtlInfo)

#endif  /*__ISE_SERVICE_MSG_H__*/
