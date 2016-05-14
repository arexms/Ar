#pragma once

#include <Ar/Raspi/Messages/RaspiMessages.pb.h>
#include <Ar/Raspi/Messages/RaspiMessage.h>

namespace Ar { namespace Raspi { namespace Messages
{
    class RaspiMessageBuilderIf
    {
    public:
        virtual ~RaspiMessageBuilderIf() {}
        virtual bool build(ArRaspiMessageEnvelope &envelope) = 0;
    };

    class RaspiMessageHeaderBuilder : public RaspiMessageBuilderIf
    {
    public:
        RaspiMessageHeaderBuilder();
        virtual bool build(ArRaspiMessageEnvelope &envelope) override;

    protected:
        void buildInterfaceVersion(ArRaspiMessageEnvelope_Header *header);
        void buildId(ArRaspiMessageEnvelope_Header *header);
        void buildTimestamp(ArRaspiMessageEnvelope_Header *header);
        void buildFrom(ArRaspiMessageEnvelope_Header *header);
        void buildTo(ArRaspiMessageEnvelope_Header *header);

    private:
        std::string _interfaceVersion;
        std::string _from;
        std::string _to;
    };

    class RaspiMessageBodyBuilder : public RaspiMessageBuilderIf
    {
    public:
        virtual bool build(ArRaspiMessageEnvelope &envelope) override;
        void setMessageAndType(unsigned type, const RaspiMessage *message);

    protected:
        void buildType(ArRaspiMessageEnvelope_Body *body);
        void buildMessage(ArRaspiMessageEnvelope_Body *body);

    private:
        unsigned _type;
        const RaspiMessage *_message;
    };


    class RaspiMessageEnvelopeBuilder : public RaspiMessageBuilderIf
    {
    public:
        RaspiMessageEnvelopeBuilder();
        virtual bool build(ArRaspiMessageEnvelope &envelope) override;
        void setHeaderBuilder(RaspiMessageBuilderIf *headerBuilder);
        void setBodyBuilder(RaspiMessageBuilderIf *bodyBuilder);

    private:
        RaspiMessageBuilderIf *_headerBuilder;
        RaspiMessageBuilderIf *_bodyBuilder;
    };
} } }
