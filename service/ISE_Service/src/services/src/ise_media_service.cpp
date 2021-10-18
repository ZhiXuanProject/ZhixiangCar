#include "ise_media_service.h"

namespace ise_service
{
    using namespace ise_common;

    CIseMediaService::CIseMediaService()
    {
        ISE_INFO_TRACE("This is ISE Media Service...");
    }

    CIseMediaService::~CIseMediaService()
    {
        ISE_INFO_TRACE("This is ISE Media Service distruct...");
    }

    ISE_BOOL CIseMediaService::OnInit()
    {

        ISE_INFO_TRACE("CIseMediaService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseMediaService::OnUninit()
    {

        ISE_INFO_TRACE("CIseMediaService un-initialized!");
    }

    ISE_VOID CIseMediaService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        if(pIseMsg->service_id != ISE_MEDIA_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseMediaService::Run()
    {
        ISE_INFO_TRACE("Enter ISE media service thread");
		CIseMediaService *pIseMediaService = CIseMediaService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseMediaService->m_MediaMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("ISE media Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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

	//This interface is called by serviceManager, put the message into the queue
    ISE_BOOL CIseMediaService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_MediaMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}