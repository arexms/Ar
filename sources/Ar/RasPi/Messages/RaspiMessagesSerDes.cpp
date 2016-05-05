#include <Ar/RasPi/Messages/RaspiMessagesSerDes.h>

namespace Ar { namespace RasPi { namespace Messages
{
    bool RaspiMessagesSerDes::serialize(const std::string &data, ArRaspiMessageEnvelope &envelope)
    {
        return serializeToEnvelope(data, envelope) && validateEnvelope(envelope);
    }

    bool RaspiMessagesSerDes::serializeToEnvelope(const std::string &data, ArRaspiMessageEnvelope &envelope)
    {
        return envelope.ParseFromString(data);
    }

    bool RaspiMessagesSerDes::validateEnvelope(const ArRaspiMessageEnvelope &envelope) const
    {
        return true;
    }


} } }
