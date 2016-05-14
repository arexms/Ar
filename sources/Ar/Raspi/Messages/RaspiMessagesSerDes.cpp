#include <Ar/Raspi/Messages/RaspiMessagesSerDes.h>

namespace Ar { namespace Raspi { namespace Messages
{
    bool RaspiMessagesSerDes::serialize(const std::string &data, RaspiMessageEnvelope &envelope)
    {
        return serializeToEnvelope(data, envelope) && validateEnvelope(envelope);
    }

    bool RaspiMessagesSerDes::serializeToEnvelope(const std::string &data, RaspiMessageEnvelope &envelope)
    {
        return envelope.ParseFromString(data);
    }

    bool RaspiMessagesSerDes::validateEnvelope(const RaspiMessageEnvelope &) const
    {
        return true;
    }


} } }
