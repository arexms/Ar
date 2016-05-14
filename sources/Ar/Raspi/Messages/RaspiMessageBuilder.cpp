#include <Ar/Raspi/Messages/RaspiMessageBuilder.h>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace Ar { namespace Raspi { namespace Messages
{
    RaspiMessageHeaderBuilder::RaspiMessageHeaderBuilder()
        : _interfaceVersion("0.0")
        , _from("Raspi_C")
        , _to("Raspi_S")
    {

}

    bool RaspiMessageHeaderBuilder::build(ArRaspiMessageEnvelope &envelope)
    {
        buildInterfaceVersion(envelope.mutable_header());
        buildId(envelope.mutable_header());
        buildTimestamp(envelope.mutable_header());
        buildFrom(envelope.mutable_header());
        buildTo(envelope.mutable_header());

        return true;
    }

    void RaspiMessageHeaderBuilder::buildInterfaceVersion(ArRaspiMessageEnvelope_Header *header)
    {
        header->set_interfaceversion(_interfaceVersion);
    }

    void RaspiMessageHeaderBuilder::buildId(ArRaspiMessageEnvelope_Header *header)
    {
        static int id = 0;
        header->set_id(id++);
    }

    void RaspiMessageHeaderBuilder::buildTimestamp(ArRaspiMessageEnvelope_Header *header)
    {
        auto now_ = std::chrono::high_resolution_clock::now();
        auto in_time_t = std::chrono::high_resolution_clock::to_time_t(now_);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        header->set_timestamp(ss.str());
    }

    void RaspiMessageHeaderBuilder::buildFrom(ArRaspiMessageEnvelope_Header *header)
    {
        header->set_from(_from);
    }

    void RaspiMessageHeaderBuilder::buildTo(ArRaspiMessageEnvelope_Header *header)
    {
        header->set_to(_to);
    }

    bool RaspiMessageBodyBuilder::build(ArRaspiMessageEnvelope &envelope)
    {
        buildType(envelope.mutable_body());
        buildMessage(envelope.mutable_body());

        return true;
    }

    void RaspiMessageBodyBuilder::setMessageAndType(unsigned type, const RaspiMessage *message)
    {
        _type = type;
        _message = message;
    }

    void RaspiMessageBodyBuilder::buildType(ArRaspiMessageEnvelope_Body *body)
    {
        body->set_type(_type);
    }

    void RaspiMessageBodyBuilder::buildMessage(ArRaspiMessageEnvelope_Body *body)
    {
        _message->SerializeToString(body->mutable_data());
    }

    RaspiMessageEnvelopeBuilder::RaspiMessageEnvelopeBuilder()
        : _headerBuilder(nullptr)
        , _bodyBuilder(nullptr)
    {

    }

    bool RaspiMessageEnvelopeBuilder::build(ArRaspiMessageEnvelope &envelope)
    {
        _headerBuilder->build(envelope);
        _bodyBuilder->build(envelope);

        return true;
    }

    void RaspiMessageEnvelopeBuilder::setHeaderBuilder(RaspiMessageBuilderIf *headerBuilder)
    {
        _headerBuilder = headerBuilder;
    }

    void RaspiMessageEnvelopeBuilder::setBodyBuilder(RaspiMessageBuilderIf *bodyBuilder)
    {
        _bodyBuilder = bodyBuilder;
    }
} } }
