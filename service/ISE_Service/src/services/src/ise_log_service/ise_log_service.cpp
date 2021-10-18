#include "ise_service_msg.h"
#include "ise_debug.h"
#include "ise_log_service.h"

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

	//This interface is called by serviceManger, this message don't need to be running in new thread
    ISE_VOID CIseLogService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        if(pIseMsg->service_id != ISE_LOG_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseLogService::Run()
    {
        ISE_INFO_TRACE("Enter ISE log service thread");
		CIseLogService *pIseLogService = CIseLogService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseLogService->m_LogMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("ISE log Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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
    ISE_BOOL CIseLogService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_LogMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}
