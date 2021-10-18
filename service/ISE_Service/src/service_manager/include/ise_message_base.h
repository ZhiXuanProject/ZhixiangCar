#ifndef __ISE_MESSAGE_BASE_H__
#define __ISE_MESSAGE_BASE_H__

#include "ise_common.h"

namespace ise_service
{
    using namespace ise_common;

    struct _ISE_ALIGN( 1 ) _ISE_PACKED ISE_MSG_HEAD
    {
        ISE_UINT8              payload_len;
        ISE_UINT8              msg_id;
        ISE_UINT16             service_id;
        ISE_UINT8              payload[0];

    public:
        ISE_MSG_HEAD(ISE_UINT16 service_id, ISE_UINT8 type, ISE_UINT8 length)
        {
            ISE_ASSERT(length >= sizeof(*this), "Invalid Message Length!");
    
            this->msg_id       = type;
            this->service_id     = service_id;
            this->payload_len    = length;
        }

        ISE_MSG_HEAD()
        {
            /*DO NOTHING*/
        }
    };
    
}


#endif  /*__ISE_MESSAGE_BASE_H__*/
