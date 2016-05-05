#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Messages.h>

namespace Ar { namespace Reset
{
    class ResetManager : public Ar::Middleware::ActiveObject
    {
    public:
        ResetManager();

        void idle();

    protected:
        void reset(ResetMessage *message);

    private:
        bool _executeReset;
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _resetThread;
    };
} }
