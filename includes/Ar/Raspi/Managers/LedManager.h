#pragma once

#include <Ar/Raspi/Managers/RaspiManagerIf.h>
#include <Ar/Middleware/SharedPtr.h>

namespace Ar { namespace Raspi { namespace Managers
{
    class LedManager : public RaspiManagerIf
    {
    public:
        LedManager(RaspiMessagesGateway *gateway);
        virtual ~LedManager();

    private:
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _thread;
        Ar::Raspi::RaspiMessagesGateway *_gateway;
    };
} } }

