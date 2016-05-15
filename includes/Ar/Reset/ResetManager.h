#pragma once

#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/SharedPtr.h>
#include <Ar/Messages.h>

namespace Ar { namespace Reset
{
    class ResetManager : public Ar::Middleware::ActiveObject
    {
    public:
        enum
        {
            SW_RESET = 1,
            SW_EXIT = 2,

            NONE
        };

        ResetManager();
        ~ResetManager();

        int idle();

    protected:
        void reset(ResetMessage *message);

    private:
        bool _executeReset;
        Ar::Middleware::SharedPtr<Ar::Middleware::ActiveThread> _resetThread;
        int _resetType;
    };
} }
