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

    bool RaspiMessageHeaderBuilder::build(RaspiMessageEnvelope &envelope)
    {
        buildInterfaceVersion(envelope.mutable_header());
        buildId(envelope.mutable_header());
        buildTimestamp(envelope.mutable_header());
        buildFrom(envelope.mutable_header());
        buildTo(envelope.mutable_header());

        return true;
    }

    void RaspiMessageHeaderBuilder::buildInterfaceVersion(RaspiMessageEnvelope_Header *header)
    {
        header->set_interfaceversion(_interfaceVersion);
    }

    void RaspiMessageHeaderBuilder::buildId(RaspiMessageEnvelope_Header *header)
    {
        static int id = 0;
        header->set_id(id++);
    }

    void RaspiMessageHeaderBuilder::buildTimestamp(RaspiMessageEnvelope_Header *header)
    {
        auto now_ = std::chrono::high_resolution_clock::now();
        auto in_time_t = std::chrono::high_resolution_clock::to_time_t(now_);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        header->set_timestamp(ss.str());
    }

    void RaspiMessageHeaderBuilder::buildFrom(RaspiMessageEnvelope_Header *header)
    {
        header->set_from(_from);
    }

    void RaspiMessageHeaderBuilder::buildTo(RaspiMessageEnvelope_Header *header)
    {
        header->set_to(_to);
    }

    bool RaspiMessageBodyBuilder::build(RaspiMessageEnvelope &envelope)
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

    void RaspiMessageBodyBuilder::buildType(RaspiMessageEnvelope_Body *body)
    {
        body->set_type(_type);
    }

    void RaspiMessageBodyBuilder::buildMessage(RaspiMessageEnvelope_Body *body)
    {
        _message->SerializeToString(body->mutable_data());
    }

    RaspiMessageEnvelopeBuilder::RaspiMessageEnvelopeBuilder()
        : _headerBuilder(nullptr)
        , _bodyBuilder(nullptr)
    {

    }

    bool RaspiMessageEnvelopeBuilder::build(RaspiMessageEnvelope &envelope)
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
