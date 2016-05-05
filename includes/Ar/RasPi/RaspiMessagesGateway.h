#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Messages.h>
#include <Ar/RasPi/Messages/RaspiMessages.pb.h>

namespace Ar { namespace RasPi
{
    class RaspiMessagesGateway : public Ar::Middleware::ActiveObject
    {
    public:
        RaspiMessagesGateway();
        ~RaspiMessagesGateway();

    protected:
        void initialize();
        void addRoute();
        void handleUdpPacketMessage(Ar::UdpPacketMessage *message);
        void serialize(Ar::UdpPacketMessage *message);
        void printHeaderAndBody(const Messages::ArRaspiMessageEnvelope &envelope) const;

    private:
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _thread;
    };
} }
