#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Messages.h>
#include <Ar/RasPi/Messages/RaspiMessages.pb.h>
#include <Ar/RasPi/Messages/RaspiMessage.h>

namespace Ar { namespace RasPi
{
    namespace Managers
    {
        class ConnectionManager;
    }

    class RaspiMessagesGateway : public Ar::Middleware::ActiveObject
    {
    public:
        RaspiMessagesGateway();
        ~RaspiMessagesGateway();

        void sendRaspiMessage(unsigned type, const Messages::RaspiMessage &message);

    protected:
        void initialize();
        void addRoute();
        void handleUdpPacketMessage(Ar::UdpPacketMessage *message);
        void serialize(Ar::UdpPacketMessage *message);
        void printHeaderAndBody(const Messages::ArRaspiMessageEnvelope &envelope) const;
        void sendIncorrectProtoBuffMessage(const Messages::ArRaspiMessageEnvelope &envelope) const;
        void dispatchMessage(const Messages::ArRaspiMessageEnvelope &);
        Messages::ArRaspiMessageEnvelope prepareEnvelope(unsigned type, const Messages::RaspiMessage &message);
        UdpPacketMessage* packToUdpPacketMessage(const Messages::ArRaspiMessageEnvelope &envelope) const;

    private:
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _thread;
        Ar::Middleware::SharedPtr<Managers::ConnectionManager> _cm;
    };
} }
