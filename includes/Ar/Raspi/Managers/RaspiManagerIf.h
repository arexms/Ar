#pragma once

#include <Ar/Middleware/ActiveObject.h>

namespace Ar { namespace Raspi { namespace Managers
{
    class RaspiManagerIf : public Ar::Middleware::ActiveObject
    {
    public:
        RaspiManagerIf(const std::string &name);
        virtual ~RaspiManagerIf();
    };
} } }
