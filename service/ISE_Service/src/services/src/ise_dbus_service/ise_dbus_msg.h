#ifndef ISE_DBUS_MSG_H
#define ISE_DBUS_MSG_H

#include <QDBusArgument>
#include <QDBusMetaType>
#include <QVector>
#include <QPoint>

namespace ise_dbus_msg {

struct VehicleInfo
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

        friend QDBusArgument &operator <<(QDBusArgument &argument,const VehicleInfo& info)
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

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,VehicleInfo& info)
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

    struct NavPosition
    {
        int stationId;
        QString stationName;
        QString stationVedio;
        QPoint stationPos;

        friend QDBusArgument &operator <<(QDBusArgument &argument,const NavPosition& nav)
        {
            argument.beginStructure();
            argument<<nav.stationId
                    <<nav.stationName
                    <<nav.stationVedio
                    <<nav.stationPos;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,NavPosition& nav)
        {
            argument.beginStructure();
            argument>>nav.stationId
                    >>nav.stationName
                    >>nav.stationVedio
                    >>nav.stationPos;
            argument.endStructure();
            return argument;
        }
    };

    struct NavMap
    {
        bool vCanPlayVideo;
        int vNavMapId; //路线id
        QString vNavMapName; //路线名
        QString vStations;  //路线图路径
        QPoint  currentPos; //当前站点
        QVector<NavPosition> vStationVec;

        friend QDBusArgument &operator <<(QDBusArgument &argument,const NavMap& map)
        {
            argument.beginStructure();
            argument<<map.vCanPlayVideo
                    <<map.vNavMapId
                    <<map.vNavMapName
                    <<map.vStations
                    <<map.currentPos
                    <<map.vStationVec;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,NavMap& map)
        {
            argument.beginStructure();
            argument>>map.vCanPlayVideo
                    >>map.vNavMapId
                    >>map.vNavMapName
                    >>map.vStations
                    >>map.currentPos
                    >>map.vStationVec;
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

    struct MeidaCtlInfo
    {
        bool    mute;
        int     volume; //播放器音量，系统音
        int     mode;   //playback mode
        int     operate = NONE; //dbus不接受自定义枚举，使用int类型表示
        int     status; //播放状态
        QString currentPath;//当前路径
        QVector<QString> paths; //音视频路径
        friend QDBusArgument &operator <<(QDBusArgument &argument,const MeidaCtlInfo& info)
        {
            argument.beginStructure();
            argument<<info.mute
                    <<info.volume
                    <<info.mode
                    <<info.operate
                    <<info.status
                    <<info.currentPath;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,MeidaCtlInfo& info)
        {
            argument.beginStructure();
            argument>>info.mute
                    >>info.volume
                    >>info.mode
                    >>info.operate
                    >>info.status
                    >>info.currentPath;
            argument.endStructure();
            return argument;
        }
    };



    struct AirConditioner
    {
        int blowing_rate;
        int bentilate_mode;
        bool cool_air_state;
        bool heat_air_state;
        bool air_conditioner_switch;
        double outdoor_temperature;

        friend QDBusArgument &operator <<(QDBusArgument &argument,const AirConditioner& air)
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

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,AirConditioner& air)
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

    struct Advertisement
    {
        int temperature;
        QString strNews;
        QString reserved;

        friend QDBusArgument &operator <<(QDBusArgument &argument,const Advertisement& adv)
        {
            argument.beginStructure();
            argument<<adv.temperature
                    <<adv.strNews
                    <<adv.reserved;
            argument.endStructure();
            return argument;
        }

        friend const QDBusArgument &operator >>(const QDBusArgument &argument,Advertisement& adv)
        {
            argument.beginStructure();
            argument>>adv.temperature
                    >>adv.strNews
                    >>adv.reserved;
            argument.endStructure();
            return argument;
        }
    };
}

Q_DECLARE_METATYPE(ise_dbus_msg::VehicleInfo)
Q_DECLARE_METATYPE(ise_dbus_msg::NavMap)
Q_DECLARE_METATYPE(ise_dbus_msg::NavPosition)
Q_DECLARE_METATYPE(ise_dbus_msg::MeidaCtlInfo)
Q_DECLARE_METATYPE(ise_dbus_msg::AirConditioner)
Q_DECLARE_METATYPE(ise_dbus_msg::Advertisement)
#endif // ISE_DBUS_MSG_H
