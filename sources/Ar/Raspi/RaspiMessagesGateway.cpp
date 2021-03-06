#include <Ar/Raspi/RaspiMessagesGateway.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Raspi/Messages/RaspiMessagesSerDes.h>
#include <Ar/Raspi/Messages/RaspiMessageBuilder.h>
#include <Ar/Raspi/Managers/ConnectionManager.h>

namespace Ar{ namespace Raspi
{
    RaspiMessagesGateway::RaspiMessagesGateway()
        : ActiveObject("RASPI_GW")
        , _thread(safeNew<ActiveThread>())
        , _cm(safeNewWith1Arg<Managers::ConnectionManager>(this))
        , _routeId(0)
    {
        _thread->start("RaspiMessagesGateway");
        attachAndInitialize(_thread.get());
    }

    RaspiMessagesGateway::~RaspiMessagesGateway()
    {

    }

    void RaspiMessagesGateway::initialize()
    {
        log().debug("initialize()");

        at()->registerReceiverForMessage(this, &RaspiMessagesGateway::handleUdpPacketMessage);
        addRoute();
    }

    void RaspiMessagesGateway::addRoute()
    {
        log().debug("addRoute()");

        auto message = Ar::Middleware::safeNew<Ar::AddUdpTrxRouteMessage>();
        Ar::Udp::UdpTrxConfig _config;
        _config.useCommonSocket = true;
        _config.rx.ip = "127.0.0.1";
        _config.rx.port = 5500;
        _config.rx.maxDataSize = 1000;
        _config.rx.use_INADDR_ANY = true;

        _config.tx.broadcastEnabled = false;
        _config.tx.ip = "127.0.0.1";
        _config.tx.port = 5600;
        message->config = _config;
        message->callbackAtName = at()->name();

        at()->sendTo("UdpService", message);

        at()->waitForResponseFor<Ar::AddUdpTrxRouteMessage>
        ([&](auto *resp)
        {
            if(resp->result != 0)
            {
                this->log().info("initialize() Route %i configured:", resp->routeId);
                this->log().info("initialize() \t RX: %s:%i", _config.rx.ip.c_str(), _config.rx.port);
                this->log().info("initialize() \t TX: %s:%i", _config.tx.ip.c_str(), _config.tx.port);

                _routeId = resp->routeId;
            }
            else
            {
                this->log().error("initialize() Configuration failed (error %i)! Route not configured!", resp->result);
            }
        },
        [&]()
        {
            this->log().error("initialize() No response. Route not configured!");
        }
        );
    }

    void RaspiMessagesGateway::handleUdpPacketMessage(Ar::UdpPacketMessage *message)
    {
        log().debug("handleUdpPacketMessage() from route %u", message->routeId);

        serialize(message);
    }

    void RaspiMessagesGateway::serialize(UdpPacketMessage *message)
    {
        Messages::RaspiMessageEnvelope envelope;
        Messages::RaspiMessagesSerDes serDes;
        std::string data = message->data.get();
        if(!serDes.serialize(data, envelope))
        {
            log().error("serialize() 1st pahse of serialization failed- probably protobuf is incorrect.");
            sendIncorrectProtoBuffMessage(envelope);
            return;
        }

        printHeaderAndBody(envelope);
        dispatchMessage(envelope);
        /** /@note temporary - for testing purposes
        @{
        */
        if(envelope.body().type() == 3)
        {
            auto message = Ar::Middleware::safeNew<Ar::ResetMessage>();
            message->byWho = "ext";
            message->reason = "end";
            at()->sendTo("Reset", message);
        }
        /**
        @}
        */
    }

    void RaspiMessagesGateway::printHeaderAndBody(const Messages::RaspiMessageEnvelope &envelope) const
    {
        log().info("printHeaderAndBody()");

        log().info("\theader");
        log().info("\t\tinterfaceVersion: %s", envelope.header().interfaceversion().c_str());
        log().info("\t\tid: %u", envelope.header().id());
        log().info("\t\tfrom: %s", envelope.header().from().c_str());
        log().info("\t\tto: %s", envelope.header().to().c_str());
        log().info("\t\ttimestamp: %s", envelope.header().timestamp().c_str());

        log().info("\tbody");
        log().info("\t\ttype: %u", envelope.body().type());
    }

    void RaspiMessagesGateway::sendIncorrectProtoBuffMessage(const Messages::RaspiMessageEnvelope &) const
    {

    }

    void RaspiMessagesGateway::dispatchMessage(const Messages::RaspiMessageEnvelope &)
    {

    }

    Messages::RaspiMessageEnvelope RaspiMessagesGateway::prepareEnvelope(unsigned type, const Messages::RaspiMessage &message)
    {
        Messages::RaspiMessageEnvelope envelope;
        Messages::RaspiMessageEnvelopeBuilder builder;
        Messages::RaspiMessageBodyBuilder bodyBuilder;
        Messages::RaspiMessageHeaderBuilder headerBuilder;
        bodyBuilder.setMessageAndType(type, &message);
        builder.setBodyBuilder(&bodyBuilder);
        builder.setHeaderBuilder(&headerBuilder);
        builder.build(envelope);

        return envelope;
    }

    UdpPacketMessage *RaspiMessagesGateway::packToUdpPacketMessage(const Messages::RaspiMessageEnvelope &envelope) const
    {
        auto msg = new UdpPacketMessage();
        msg->length = envelope.ByteSize();
        msg->routeId = _routeId;

        char *data_ = Middleware::safeNewArray< char >( msg->length );
        envelope.SerializeToArray(data_, msg->length);
        msg->data = data_;

        return msg;
    }

    void RaspiMessagesGateway::sendRaspiMessage(unsigned type, const Messages::RaspiMessage &message)
    {
        log().debug("sendUdpPacketMessage()");

        auto &&envelope = prepareEnvelope(type, message);
        auto msg = packToUdpPacketMessage(envelope);

        at()->sendTo("UdpService", msg);
    }
} }
