#include "ise_udp_service.h"

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

	//This interface is called by serviceManger, this message don't need to be running in new thread
    ISE_VOID CIseUdpService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        if(pIseMsg->service_id != ISE_UDP_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseUdpService::Run()
    {
        ISE_INFO_TRACE("Enter Udp service thread");
		CIseUdpService *pIseUdpService = CIseUdpService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseUdpService->m_UdpMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("Udp Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

                if(pServiceMsg->service_id != ISE_SERVICE_ID_UNKNOWN)
                {
                    ISE_ERROR_TRACE("Invalid ISE Message! Ignore!!!!");
                    continue;
                }
				//
				//To do something at here, if need other service to handle this message,please rebuild the 
				//serveceMsg with target service ID and filled it with new data then call the service manager interface
				//of OnMessage or SendIseServiceMsg.
				//
            }
            else
            {
                ISE_INFO_TRACE("Wait timeout. Continue to wait...");
            }
        }
    }

	//This interface is called by serviceManager ,put the message into the queue
    ISE_BOOL CIseUdpService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_UdpMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}