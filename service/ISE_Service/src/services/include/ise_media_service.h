#ifndef ISE_MEDIA_SERVICE_H
#define ISE_MEDIA_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    using namespace ise_common;

    class CIseMediaService : public CIseServiceBase, public CSingleton<CIseMediaService>
    {
    public:
        CIseMediaService();
        virtual ~CIseMediaService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID        OnMessage(const ISE_MSG_HEAD *pPepMsg);

    };
}

#endif  /*__ISE_MEDIA_SERVICE_H__*/
