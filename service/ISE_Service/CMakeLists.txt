cmake_minimum_required(VERSION 3.0.2)
project(ise_service)

## Compile as C++11
add_compile_options(-std=c++11 -pthread)

include_directories(
   src/common/include
   src/service_manager/include
   src/services/include
)

## Declare a C++ library
add_library(ise_common
   src/common/src/ise_debug.cpp
   src/common/src/ise_thread.cpp
   src/common/src/ise_utils.cpp
)

add_library(ise_service_manager
   src/service_manager/src/ise_service_base.cpp
   src/service_manager/src/ise_service_manager.cpp
)

add_library(ise_services
   src/services/src/ise_can_service.cpp
   src/services/src/ise_dbus_service.cpp
   src/services/src/ise_udp_service.cpp
   src/services/src/ise_log_service.cpp
   src/services/src/ise_map_service.cpp
   src/services/src/ise_media_service.cpp
   src/services/src/ise_update_service.cpp
   src/services/src/ise_usb_service.cpp
   src/services/src/ise_web_scribe_service.cpp
)

## Declare a C++ executable
add_executable(IseService src/ISE_Service_Main.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(IseService
   ise_service_manager
   ise_services
   ise_common
   -lpthread
 )
