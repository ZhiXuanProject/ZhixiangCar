#ifndef ISE_MAP_SERVICE_H
#define ISE_MAP_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    using namespace ise_common;

    class CIseMapService : public CIseServiceBase, public CSingleton<CIseMapService>
    {
    public:
        CIseMapService();
        virtual ~CIseMapService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);

    };
}

#endif  /*__ISE_MAP_SERVICE_H__*/
