#include "ise_dbus_service.h"
#include "vehiclebusproxy.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseDbusService::CIseDbusService()
    {
        ISE_INFO_TRACE("This is ISE dbus Service...");
    }

    CIseDbusService::~CIseDbusService()
    {
        ISE_INFO_TRACE("This is ISE dbus Service distruct...");
    }

    ISE_BOOL CIseDbusService::OnInit()
    {
        //初始化dbus
        VehicleDbusProxy::getInstance()->initBus();

        ISE_INFO_TRACE("CIseDbusService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseDbusService::OnUninit()
    {

        ISE_INFO_TRACE("CIseDbusService un-initialized!");
    }

    ISE_VOID CIseDbusService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}
