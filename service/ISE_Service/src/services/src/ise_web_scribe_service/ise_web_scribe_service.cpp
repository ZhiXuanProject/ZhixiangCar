#include "ise_web_scribe_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"
#include "advertisementinfo.h"


namespace ise_service
{
    using namespace ise_common;

    CIseWebSubscribeService::CIseWebSubscribeService()
    {
        ISE_INFO_TRACE("This is ISE WebScribe Service...");
    }

    CIseWebSubscribeService::~CIseWebSubscribeService()
    {
        ISE_INFO_TRACE("This is ISE WebScribe Service distruct...");
    }

    ISE_BOOL CIseWebSubscribeService::OnInit()
    {
        m_Advinfo = new AdvertisementInfo;
        ISE_INFO_TRACE("CIseWebScribeService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseWebSubscribeService::OnUninit()
    {

        ISE_INFO_TRACE("CIseWebScribeService un-initialized!");
    }

    ISE_VOID CIseWebSubscribeService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}
