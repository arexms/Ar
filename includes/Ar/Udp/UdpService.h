#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/Logger.h>
#include <Ar/Common.h>
#include <map>

namespace Ar { namespace Middleware
{
    class ActiveThread;
} }

namespace Ar
{
    struct AddUdpTrxRouteMessage;
    struct UdpPacketMessage;
}

namespace Ar { namespace Udp
{
    class UdpTrx;
    struct UdpTrxConfig;

    class UdpService : public Ar::Middleware::ActiveObject
    {
        static unsigned nextRouteId;
    public:
        UdpService();
        ~UdpService();
        void initialize();
        void run();

        void sendUdpPacket(UdpPacketMessage *message);

    protected:
        class Route
        {
        public:
            Route(UdpService *service, const std::string &callbackAtName);
            ~Route();
            unsigned initialize(const UdpTrxConfig &config);
            void sendUdpPacket(UdpPacketMessage *message);

        protected:
            void handleUdpPacket(DataPtr &data, unsigned length);
            void sendUdpPacketInternally(DataPtr &data, unsigned length);

            inline Middleware::Logger& log();

        private:
            UdpService *_service;
            unsigned _routeId;
            std::string _callbackAtName;
            UdpTrx* _trx;
        };

        void registerForMessages();
        void handleAddUdpTrxRouteMessage(AddUdpTrxRouteMessage *message);
        unsigned addUdpTrxRoute(AddUdpTrxRouteMessage *message);
        unsigned add(Route *route);

    private:
        Ar::Middleware::ActiveThread *_at;
        std::map<unsigned, Route*> _routes;
    };

    // IMPLEMENTATION
    inline Middleware::Logger& UdpService::Route::log()
    {
        return _service->log();
    }
} }
