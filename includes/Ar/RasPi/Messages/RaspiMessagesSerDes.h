#pragma once

#include <Ar/RasPi/Messages/RaspiMessages.pb.h>

namespace Ar { namespace RasPi { namespace Messages
{
    class RaspiMessagesSerDes
    {
    public:
        bool serialize(const std::string &data, ArRaspiMessageEnvelope &envelope);

    protected:
        bool serializeToEnvelope(const std::string &data, ArRaspiMessageEnvelope &envelope);
        bool validateEnvelope(const ArRaspiMessageEnvelope &envelope) const;

    };

} } }
