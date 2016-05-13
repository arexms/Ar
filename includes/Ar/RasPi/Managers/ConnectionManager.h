#pragma once

#include <Ar/RasPi/Managers/RaspiManagerIf.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Middleware/Timer.h>

namespace Ar { namespace RasPi
{
    class RaspiMessagesGateway;
} }

namespace Ar { namespace RasPi { namespace Managers
{
    class ConnectionManager : public RaspiManagerIf
    {
    public:
        ConnectionManager(RaspiMessagesGateway *gateway);
        virtual ~ConnectionManager();

    protected:
        virtual void initialize() override;
        void sendStatus();

    private:
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _thread;
        Ar::Middleware::Timer _timer;
        Ar::RasPi::RaspiMessagesGateway *_gateway;
    };
} } }
