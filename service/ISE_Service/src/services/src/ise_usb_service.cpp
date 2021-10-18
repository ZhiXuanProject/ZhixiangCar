#include "ise_usb_service.h"

namespace ise_service
{
    using namespace ise_common;

    CIseUsbService::CIseUsbService()
    {
        ISE_INFO_TRACE("This is ISE USB Service...");
    }

    CIseUsbService::~CIseUsbService()
    {
        ISE_INFO_TRACE("This is ISE USB Service distruct...");
    }

    ISE_BOOL CIseUsbService::OnInit()
    {

        ISE_INFO_TRACE("CIseUsbService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseUsbService::OnUninit()
    {

        ISE_INFO_TRACE("CIseUsbService un-initialized!");
    }

    ISE_VOID CIseUsbService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        if(pIseMsg->service_id != ISE_USB_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseUsbService::Run()
    {
        ISE_INFO_TRACE("Enter ISE usb service thread");
		CIseUsbService *pIseUsbService = CIseUsbService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseUsbService->m_UsbMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("ISE usb Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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

	//This interface is called by serviceManager, put message into the queue
    ISE_BOOL CIseUsbService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_UsbMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}