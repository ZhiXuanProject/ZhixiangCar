QT += core gui dbus network

TARGET = ISE_Service
CONFIG += c++11
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./src/common/include
INCLUDEPATH += ./src/service_manager/include
INCLUDEPATH += ./src/services/include

HEADERS += src/common/include/ise_common.h \
    src/common/include/ise_debug.h \
    src/common/include/ise_queue.h \
    src/common/include/ise_singleton.h \
    src/common/include/ise_thread.h \
    src/common/include/ise_utils.h \
    src/service_manager/include/ise_message_base.h \
    src/service_manager/include/ise_service_base.h \
    src/service_manager/include/ise_service_manager.h \
    src/service_manager/include/ise_service_msg.h \
    src/services/include/ise_can_service.h \
    src/services/include/ise_dbus_service.h \
    src/services/include/ise_log_service.h \
    src/services/include/ise_map_service.h \
    src/services/include/ise_media_service.h \
    src/services/include/ise_update_service.h \
    src/services/include/ise_udp_service.h \
    src/services/include/ise_web_scribe_service.h \
    src/services/src/ise_dbus_service/vehiclenavdisplayadaptor.h \
    src/services/src/ise_dbus_service/vehiclemediacontroladaptor.h \
    src/services/src/ise_dbus_service/vehicleinformationadaptor.h \
    src/services/src/ise_dbus_service/vehiclebusproxy.h

SOURCES += src/common/src/ise_debug.cpp \
    src/common/src/ise_thread.cpp \
    src/common/src/ise_utils.cpp \
    src/service_manager/src/ise_service_base.cpp \
    src/service_manager/src/ise_service_manager.cpp \
    src/services/src/ise_can_service/ise_can_service.cpp \
    src/services/src/ise_dbus_service/ise_dbus_service.cpp \
    src/services/src/ise_log_service/ise_log_service.cpp \
    src/services/src/ise_map_service/ise_map_service.cpp \
    src/services/src/ise_media_service/ise_media_service.cpp \
    src/services/src/ise_update_service/ise_update_service.cpp \
    src/services/src/ise_udp_service/ise_udp_service.cpp \
    src/services/src/ise_web_scribe_service/ise_web_scribe_service.cpp \
    src/ISE_Service_Main.cpp \
    src/services/src/ise_dbus_service/vehiclenavdisplayadaptor.cpp \
    src/services/src/ise_dbus_service/vehiclemediacontroladaptor.cpp \
    src/services/src/ise_dbus_service/vehicleinformationadaptor.cpp \
    src/services/src/ise_dbus_service/vehiclebusproxy.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
