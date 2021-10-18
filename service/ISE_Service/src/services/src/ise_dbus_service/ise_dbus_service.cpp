#include "ise_dbus_service.h"
#include "vehiclebusproxy.h"

namespace ise_service
{
    using namespace ise_common;

    CIseDbusService::CIseDbusService()
    {
        ISE_INFO_TRACE("This is ISE dbus Service...");
    }

    CIseDbusService::~CIseDbusService()
    {
        ISE_INFO_TRACE("This is ISE dbus Service distruct...");
    }

    ISE_BOOL CIseDbusService::OnInit()
    {
        //初始化dbus
        VehicleDbusProxy::getInstance()->initBus();

        ISE_INFO_TRACE("CIseDbusService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseDbusService::OnUninit()
    {

        ISE_INFO_TRACE("CIseDbusService un-initialized!");
    }

	//This interface is called by serviceManger, this message don't need to be running in new thread
    ISE_VOID CIseDbusService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        if(pIseMsg->service_id != ISE_DBUS_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }


        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseDbusService::Run()
    {
        ISE_INFO_TRACE("Enter Dbus service thread");
		CIseDbusService *pIseDbusService = CIseDbusService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseDbusService->m_DbusMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("Dbus Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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
    ISE_BOOL CIseDbusService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_DbusMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}
