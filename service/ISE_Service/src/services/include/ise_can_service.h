#ifndef ISE_CAN_SERVICE_H
#define ISE_CAN_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    class CIseCanService : public CIseServiceBase, public CSingleton<CIseCanService>
    {
    public:
        CIseCanService();
        virtual ~CIseCanService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID          OnMessage(const ISE_MSG_HEAD *pServiceMsg);
    };
}

#endif  /*ISE_CAN_SERVICE_H*/
