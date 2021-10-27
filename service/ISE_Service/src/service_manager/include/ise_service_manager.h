#ifndef ISE_SERVICE_MANAGER_H
#define ISE_SERVICE_MANAGER_H

#include "ise_common.h"
#include "ise_service_base.h"
#include<map>

namespace ise_service
{
    class CIseServiceManager : public CSingleton<CIseServiceManager>
    {
    public:
        CIseServiceManager();
        ~CIseServiceManager();

    public:
        ISE_BOOL                                Init();
        ISE_VOID                                Uninit();

    public:
        CIseServicePtr                          GetServiceInstance(ISE_UINT16 service_id);
	private:
		std::map<ISE_UINT16, CIseServicePtr>    m_ServiceMap;
	};
    //ISE_BOOL            ExtSendIseServiceMsg(ISE_UINT16 service_id, ISE_MSG_HEAD *pServiceMsg);
}


#endif  /*__ISE_SERVICE_MANAGER_H__*/
