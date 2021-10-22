#include "ise_map_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseMapService::CIseMapService()
    {
        ISE_INFO_TRACE("This is ISE Map Service...");
    }

    CIseMapService::~CIseMapService()
    {
        ISE_INFO_TRACE("This is ISE Map Service distruct...");
    }

    ISE_BOOL CIseMapService::OnInit()
    {

        ISE_INFO_TRACE("CIseMapService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseMapService::OnUninit()
    {

        ISE_INFO_TRACE("CIseMapService un-initialized!");
    }

    ISE_VOID CIseMapService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}