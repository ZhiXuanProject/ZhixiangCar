#include "ise_web_scribe_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseWebScribeService::CIseWebScribeService()
    {
        ISE_INFO_TRACE("This is ISE WebScribe Service...");
    }

    CIseWebScribeService::~CIseWebScribeService()
    {
        ISE_INFO_TRACE("This is ISE WebScribe Service distruct...");
    }

    ISE_BOOL CIseWebScribeService::OnInit()
    {

        ISE_INFO_TRACE("CIseWebScribeService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseWebScribeService::OnUninit()
    {

        ISE_INFO_TRACE("CIseWebScribeService un-initialized!");
    }

    ISE_VOID CIseWebScribeService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}