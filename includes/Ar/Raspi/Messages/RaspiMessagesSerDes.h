#pragma once

#include <Ar/Raspi/Messages/RaspiMessages.pb.h>

namespace Ar { namespace Raspi { namespace Messages
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
