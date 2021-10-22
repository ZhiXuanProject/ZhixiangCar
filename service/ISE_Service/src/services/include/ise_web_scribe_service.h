#ifndef ISE_WEB_SCRIBE_SERVICE_H
#define ISE_WEB_SCRIBE_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    using namespace ise_common;

    class CIseWebScribeService : public CIseServiceBase, public CSingleton<CIseWebScribeService>
    {
    public:
        CIseWebScribeService();
        virtual ~CIseWebScribeService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);

    };
}

#endif  /*__ISE_WEB_SCRIBE_SERVICE_H__*/
