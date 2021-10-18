#include "ise_map_service.h"

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
        if(pIseMsg->service_id != ISE_MAP_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseMapService::Run()
    {
        ISE_INFO_TRACE("Enter ISE map service thread");
		CIseMapService *pIseMapService = CIseMapService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseMapService->m_MapMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("ISE map Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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

	//This interface is called by serviceManager, put the message into queue
    ISE_BOOL CIseMapService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_MapMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}