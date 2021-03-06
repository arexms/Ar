#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Messages.h>
#include <Ar/Raspi/Messages/RaspiMessages.pb.h>
#include <Ar/Raspi/Messages/RaspiMessage.h>

namespace Ar { namespace Raspi
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
        void printHeaderAndBody(const Messages::RaspiMessageEnvelope &envelope) const;
        void sendIncorrectProtoBuffMessage(const Messages::RaspiMessageEnvelope &envelope) const;
        void dispatchMessage(const Messages::RaspiMessageEnvelope &);
        Messages::RaspiMessageEnvelope prepareEnvelope(unsigned type, const Messages::RaspiMessage &message);
        UdpPacketMessage* packToUdpPacketMessage(const Messages::RaspiMessageEnvelope &envelope) const;

    private:
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _thread;
        Ar::Middleware::SharedPtr<Managers::ConnectionManager> _cm;
        unsigned _routeId;
    };
} }
