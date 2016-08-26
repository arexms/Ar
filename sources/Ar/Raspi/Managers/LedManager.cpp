#include <Ar/Raspi/Managers/LedManager.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Raspi/RaspiMessagesGateway.h>

namespace Ar { namespace Raspi { namespace Managers
{
    LedManager::LedManager(RaspiMessagesGateway *gateway)
        : RaspiManagerIf("LED_MNGR")
        , _thread(Ar::Middleware::ActiveThread::create())
        , _gateway(gateway)
    {
        _thread->start("ConnMngr");
        attachAndInitialize(_thread.get());
    }

    LedManager::~LedManager()
    {

    }
} } }
