#include "ise_udp_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseUdpService::CIseUdpService()
    {
        ISE_INFO_TRACE("This is ISE udp Service...");
    }

    CIseUdpService::~CIseUdpService()
    {
        ISE_INFO_TRACE("This is ISE udp Service distruct...");
    }

    ISE_BOOL CIseUdpService::OnInit()
    {

        ISE_INFO_TRACE("CIseUdpService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseUdpService::OnUninit()
    {

        ISE_INFO_TRACE("CIseUdpService un-initialized!");
    }

    ISE_VOID CIseUdpService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}