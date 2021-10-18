#ifndef __ISE_SERVICE_MANAGER_H__
#define __ISE_SERVICE_MANAGER_H__

#include "ise_common.h"
#include "ise_message_base.h"

#include "ise_service_base.h"

#include<map>

namespace ise_service
{
    using namespace ise_common;

    class CIseServiceManager : public CSingleton<CIseServiceManager>
    {
    public:
        CIseServiceManager();
        ~CIseServiceManager();

    public:
        ISE_BOOL                                Init();
        ISE_VOID                                Uninit();

    public:
        ISE_VOID                                OnMessage(const ISE_MSG_HEAD *pServiceMsg);
		ISE_BOOL 							    SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg);

    public:
        CIseServicePtr                          GetServiceInstance(ISE_UINT16 service_id);
	public:
		static ISE_VOID     					*ServiceManagerThread(ISE_VOID *pParam);
	private:
		ISE_BOOL                                InitServiceManagerThread();

    private:
		CIseQueue<ISE_MSG_HEAD *>              m_MessageQueue;
		CIseThread                         	   *m_pServiceManagerThread;
		std::map<ISE_UINT16, CIseServicePtr>   m_ServiceMap;
    };
	
}


#endif  /*__ISE_SERVICE_MANAGER_H__*/