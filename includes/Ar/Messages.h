#pragma once

#include <Ar/Middleware/IMessage.h>
#include <Ar/Udp/UdpTrxConfig.h>
#include <Ar/Common.h>

namespace Ar {
    using namespace Middleware;

    struct OtherMessage : public IMessage
    {
        struct Response : public IMessage::IResponse
        {
            Response(IMessage *message)
                : IMessage::IResponse(message)
            {}
            static MessageId MSG_ID() { return MessageId::OTHER_RESPONSE; }
            virtual MessageId id() { return MessageId::OTHER_RESPONSE; }
        };

        static MessageId MSG_ID() { return MessageId::OTHER; }
        virtual MessageId id() { return MessageId::OTHER; }
        virtual Response* createResponse()
        {
            return IMessage::createResponse(this);
        }

        std::string str;


    };

    struct ResetMessage : public IMessage
    {
        struct Response : public IMessage::IResponse
        {
            RESPONSE(MessageId::RESET_RESPONSE)
        };

        MESSAGE(MessageId::RESET)

        std::string byWho;
        std::string reason;
    };

    struct AddUdpTrxRouteMessage : public IMessage
    {
        struct Response : public IMessage::IResponse
        {
            RESPONSE(MessageId::ADD_UDP_TRX_ROUTE_RESPONSE)
            unsigned routeId;
        };

        MESSAGE(MessageId::ADD_UDP_TRX_ROUTE)

        Udp::UdpTrxConfig config;
        std::string callbackAtName;
    };

    struct UdpPacketMessage : public IMessage
    {
        struct Response : public IMessage::IResponse
        {
            RESPONSE(MessageId::UDP_PACKET_RESPONSE)
        };
        MESSAGE(MessageId::UDP_PACKET)

        DataPtr data;
        unsigned length;
        unsigned routeId;
    };
}
