#include "ise_service_msg.h"
#include "ise_log_service.h"
#include "ise_service_manager.h"

namespace ise_service
{
    CIseLogService::CIseLogService()
    {
        ISE_INFO_TRACE("This is ISE Log Service...");
    }

    CIseLogService::~CIseLogService()
    {
        ISE_INFO_TRACE("This is ISE Log Service distruct...");
    }

    ISE_BOOL CIseLogService::OnInit()
    {

        ISE_INFO_TRACE("CIseLogService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseLogService::OnUninit()
    {

        ISE_INFO_TRACE("CIseLogService un-initialized!");
    }

    ISE_VOID CIseLogService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->msg_id);
    }

}
