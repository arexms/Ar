#include <Ar/RasPi/RaspiMessagesGateway.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/RasPi/Messages/RaspiMessagesSerDes.h>

namespace Ar{ namespace RasPi
{
    RaspiMessagesGateway::RaspiMessagesGateway()
        : ActiveObject(Ar::Middleware::RASPI_GW)
        , _thread(safeNew<ActiveThread>())
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
        log().debug("handleUdpPacketMessage()");

        serialize(message);
    }

    void RaspiMessagesGateway::serialize(UdpPacketMessage *message)
    {
        Messages::ArRaspiMessageEnvelope envelope;
        Messages::RaspiMessagesSerDes serDes;
        std::string data = message->data.get();
        if(!serDes.serialize(data, envelope))
        {
            log().error("serialize() ERROR");
            /// @todo send error message
            return;
        }

        printHeaderAndBody(envelope);
    }

    void RaspiMessagesGateway::printHeaderAndBody(const Messages::ArRaspiMessageEnvelope &envelope) const
    {
        log().info("printHeaderAndBody()");

        log().info("\theader");
        log().info("\t\tinterfaceVersion: %s", envelope.header().interfaceversion().c_str());
        log().info("\t\tid: %u", envelope.header().id());
        log().info("\t\tfrom: %s", envelope.header().from().c_str());

        log().info("\tbody");
        log().info("\t\tversion: %s", envelope.body().version().c_str());
        log().info("\t\ttype: %u", envelope.body().type());
    }
} }
