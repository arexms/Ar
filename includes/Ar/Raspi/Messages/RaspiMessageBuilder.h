#pragma once

#include <Ar/Raspi/Messages/RaspiMessages.pb.h>
#include <Ar/Raspi/Messages/RaspiMessage.h>

namespace Ar { namespace Raspi { namespace Messages
{
    class RaspiMessageBuilderIf
    {
    public:
        virtual ~RaspiMessageBuilderIf() {}
        virtual bool build(RaspiMessageEnvelope &envelope) = 0;
    };

    class RaspiMessageHeaderBuilder : public RaspiMessageBuilderIf
    {
    public:
        RaspiMessageHeaderBuilder();
        virtual bool build(RaspiMessageEnvelope &envelope) override;
        RaspiMessageHeaderBuilder& setInterfaceVersion(const std::string &interfaceVersion);
        RaspiMessageHeaderBuilder& setFrom(const std::string &from);
        RaspiMessageHeaderBuilder& setTo(const std::string &to);

    protected:
        bool buildInterfaceVersion(RaspiMessageEnvelope_Header *header);
        bool buildId(RaspiMessageEnvelope_Header *header);
        bool buildTimestamp(RaspiMessageEnvelope_Header *header);
        bool buildFrom(RaspiMessageEnvelope_Header *header);
        bool buildTo(RaspiMessageEnvelope_Header *header);

    private:
        std::string _interfaceVersion;
        std::string _from;
        std::string _to;
    };

    class RaspiMessageBodyBuilder : public RaspiMessageBuilderIf
    {
    public:
        virtual bool build(RaspiMessageEnvelope &envelope) override;
        RaspiMessageBodyBuilder& setMessageAndType(unsigned type, const RaspiMessage *message);

    protected:
        bool buildType(RaspiMessageEnvelope_Body *body);
        bool buildMessage(RaspiMessageEnvelope_Body *body);

    private:
        unsigned _type;
        const RaspiMessage *_message;
    };


    class RaspiMessageEnvelopeBuilder : public RaspiMessageBuilderIf
    {
    public:
        RaspiMessageEnvelopeBuilder();
        virtual bool build(RaspiMessageEnvelope &envelope) override;
        RaspiMessageEnvelopeBuilder& setHeaderBuilder(RaspiMessageBuilderIf *headerBuilder);
        RaspiMessageEnvelopeBuilder& setBodyBuilder(RaspiMessageBuilderIf *bodyBuilder);

    private:
        RaspiMessageBuilderIf *_headerBuilder;
        RaspiMessageBuilderIf *_bodyBuilder;
    };
} } }
