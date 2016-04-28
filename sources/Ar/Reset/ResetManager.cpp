#include <Ar/Reset/ResetManager.h>
#include <Ar/Middleware/ActiveThread.h>
#include <thread>

namespace Ar { namespace Reset
{
    using namespace Ar::Middleware;

    ResetManager::ResetManager()
        : _executeReset(false)
        , _resetThread(safeNew<ActiveThread>())
        , _log(RESET)
    {
        _resetThread->start("Reset");
        attachTo(_resetThread.get());

        at()->registerReceiverForMessage(this, &ResetManager::reset);
    }

    void ResetManager::idle()
    {
        while(!_executeReset)
        {
            using namespace std::literals;
            std::this_thread::sleep_for(1s);
        }
    }

    void ResetManager::reset(ResetMessage *message)
    {
        log().warning("Reset Received!");
        log().info("\t%s(%s)", message->byWho.c_str(), message->from->name().c_str());
        log().info("\t%s", message->reason.c_str());
        _executeReset = true;
    }
} }
