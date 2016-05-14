#pragma once

#include <Ar/Raspi/Messages/RaspiMessages.pb.h>

namespace Ar { namespace Raspi { namespace Messages
{
    class RaspiMessagesSerDes
    {
    public:
        bool serialize(const std::string &data, RaspiMessageEnvelope &envelope);

    protected:
        bool serializeToEnvelope(const std::string &data, RaspiMessageEnvelope &envelope);
        bool validateEnvelope(const RaspiMessageEnvelope &envelope) const;

    };

} } }
