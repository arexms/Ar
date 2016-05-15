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
        return
                buildInterfaceVersion(envelope.mutable_header()) &&
                buildId(envelope.mutable_header()) &&
                buildTimestamp(envelope.mutable_header()) &&
                buildFrom(envelope.mutable_header()) &&
                buildTo(envelope.mutable_header());
    }

    RaspiMessageHeaderBuilder& RaspiMessageHeaderBuilder::setInterfaceVersion(const std::string &interfaceVersion)
    {
        _interfaceVersion = interfaceVersion;
        return *this;
    }

    RaspiMessageHeaderBuilder& RaspiMessageHeaderBuilder::setFrom(const std::string &from)
    {
        _from = from;
        return *this;
    }

    RaspiMessageHeaderBuilder& RaspiMessageHeaderBuilder::setTo(const std::string &to)
    {
        _to = to;
        return *this;
    }

    bool RaspiMessageHeaderBuilder::buildInterfaceVersion(RaspiMessageEnvelope_Header *header)
    {
        header->set_interfaceversion(_interfaceVersion);

        return true;
    }

    bool RaspiMessageHeaderBuilder::buildId(RaspiMessageEnvelope_Header *header)
    {
        static int id = 0;
        header->set_id(id++);

        return true;
    }

    bool RaspiMessageHeaderBuilder::buildTimestamp(RaspiMessageEnvelope_Header *header)
    {
        auto now_ = std::chrono::high_resolution_clock::now();
        auto in_time_t = std::chrono::high_resolution_clock::to_time_t(now_);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        header->set_timestamp(ss.str());

        return true;
    }

    bool RaspiMessageHeaderBuilder::buildFrom(RaspiMessageEnvelope_Header *header)
    {
        header->set_from(_from);

        return true;
    }

    bool RaspiMessageHeaderBuilder::buildTo(RaspiMessageEnvelope_Header *header)
    {
        header->set_to(_to);

        return true;
    }

    bool RaspiMessageBodyBuilder::build(RaspiMessageEnvelope &envelope)
    {
        return buildType(envelope.mutable_body()) && buildMessage(envelope.mutable_body());
    }

    RaspiMessageBodyBuilder& RaspiMessageBodyBuilder::setMessageAndType(unsigned type, const RaspiMessage *message)
    {
        _type = type;
        _message = message;

        return *this;
    }

    bool RaspiMessageBodyBuilder::buildType(RaspiMessageEnvelope_Body *body)
    {
        body->set_type(_type);
        return true;
    }

    bool RaspiMessageBodyBuilder::buildMessage(RaspiMessageEnvelope_Body *body)
    {
        auto ret = _message->SerializeToString(body->mutable_data());
        return ret;
    }

    RaspiMessageEnvelopeBuilder::RaspiMessageEnvelopeBuilder()
        : _headerBuilder(nullptr)
        , _bodyBuilder(nullptr)
    {

    }

    bool RaspiMessageEnvelopeBuilder::build(RaspiMessageEnvelope &envelope)
    {
        return _headerBuilder->build(envelope) && _bodyBuilder->build(envelope);
    }

    RaspiMessageEnvelopeBuilder &RaspiMessageEnvelopeBuilder::setHeaderBuilder(RaspiMessageBuilderIf *headerBuilder)
    {
        _headerBuilder = headerBuilder;

        return *this;
    }

    RaspiMessageEnvelopeBuilder &RaspiMessageEnvelopeBuilder::setBodyBuilder(RaspiMessageBuilderIf *bodyBuilder)
    {
        _bodyBuilder = bodyBuilder;

        return *this;
    }
} } }
