#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/ActiveThreadAddresses.h>
#include <Ar/Messages.h>
#include <Ar/Udp/UdpService.h>
#include <Ar/Reset/ResetManager.h>
#include <Ar/RasPi/RaspiMessagesGateway.h>

/*class A : public Ar::Middleware::ActiveObject
{
    Ar::Middleware::ActiveThread _at;

public:
    A()
        : ActiveObject(Ar::Middleware::GENERIC)
    {
        _at.start("A thread");
        attachTo(&_at);

        at()->registerReceiverForMessage(this, &A::f);
        at()->registerReceiverForMessage(this, &A::handleUdpPacketMessage);
    }

    void run()
    {
        auto message = Ar::Middleware::safeNew<Ar::OtherMessage>();
        std::cout << "First: ";
        //std::cin >> message->str;
        message->str = "bla";

        at()->sendTo("B thread", message);
    }

    void start()
    {
        for(;;)
        {
            std::string str;
            std::cout << "What to send: ";
            std::cin >> str;
            if(str == "exit")
            {
                sendReset();
                break;
            }
            else if(str == "udp")
            {
                sendUdp();
                break;
            }
            auto message = Ar::Middleware::safeNew<Ar::OtherMessage>();
            message->str = str;
            at()->sendTo("B thread", message);

            at()->waitForResponseFor<Ar::OtherMessage>
            (
                [](auto *resp)
                {
                    std::cout << "Received resp: " << resp->result << ", from " << resp->from->name() << "\n";
                },
                []()
                {
                    std::cout << "No response!\n";
                }
            );
        }
    }

    void sendReset()
    {
        auto message = Ar::Middleware::safeNew<Ar::ResetMessage>();
        message->byWho = "A";
        message->reason = "end";
        at()->sendTo("Reset", message);
    }

    void sendUdp()
    {
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
        ([](auto *resp)
        {
            std::cout << "Received resp for udp: " << resp->result<< ", " << resp->routeId  << "\n";
        },
        []()
        {
            std::cout << "No response for udp!\n";
        }
        );

        sendUdp2();
    }

    void sendUdp2()
    {
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
        ([](auto *resp)
        {
            std::cout << "Received resp for udp: " << resp->result<< ", " << resp->routeId  << "\n";
        },
        []()
        {
            std::cout << "No response for udp!\n";
        }
        );
    }

    void handleUdpPacketMessage(Ar::UdpPacketMessage *message)
    {
        std::cout << "Received UdpPacketMessage: Route:" << message->routeId << ", from " << message->from->name() << ",'" << message->data.get() << "'\n";
        std::string str = message->data.get();
        if(str == "exit")
        {
            std::cout << "Reseting...\n";
            sendReset();
        }
    }

    void f(Ar::OtherMessage::Response *message)
    {
        std::cout << "Received response: " << message->result << ", from " << message->from->name() << "\n";
        start();
    }
};

class B : public Ar::Middleware::ActiveObject
{
    static int i;
    Ar::Middleware::ActiveThread _at;

public:
    B()
    : ActiveObject(Ar::Middleware::GENERIC)
    {
        _at.start("B thread");
        attachTo(&_at);
        at()->registerReceiverForMessage(this, &B::f);
    }

    void f(Ar::OtherMessage *message)
    {
        std::cout << "Received: " << message->str << "\n";
        std::cout << "Creating response" << "\n";
        auto response = message->createResponse();
        response->result = ++i;
        at()->sendTo(message->from, response);
    }
};

int B::i = 0;*/

int main()
{
    Ar::Udp::UdpService udpService;
    udpService.initialize();
    udpService.run();
    Ar::Reset::ResetManager resetManager;
    Ar::RasPi::RaspiMessagesGateway raspiMessagesGateway;

    resetManager.idle();

    return 0;
}
