#ifndef __ISE_MAP_SERVICE_H__
#define __ISE_MAP_SERVICE_H__

#include "ise_common.h"
#include "ise_service_base.h"
#include "ise_service_msg.h"

namespace ise_service
{
    using namespace ise_common;

    class CIseMapService : public CIseServiceBase, public CSingleton<CIseMapService>
    {
    public:
        CIseMapService();
        ~CIseMapService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);
		virtual ISE_VOID       Run();
		ISE_BOOL               SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg);

	private:
		CIseQueue<ISE_MSG_HEAD *>          m_MapMessageQueue;

    };
}

#endif  /*__ISE_MAP_SERVICE_H__*/