#include <Ar/Raspi/Managers/ConnectionManager.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Middleware/Utils.h>
#include <Ar/Raspi/Messages/RaspiMessages.pb.h>
#include <Ar/Raspi/RaspiMessagesGateway.h>
#include <Ar/Messages.h>

namespace Ar { namespace Raspi { namespace Managers
{
    ConnectionManager::ConnectionManager(RaspiMessagesGateway *gateway)
        : RaspiManagerIf("CONN_MNGR")
        , _thread(Ar::Middleware::ActiveThread::create())
        , _gateway(gateway)
    {
        _thread->start("ConnMngr");
        attachAndInitialize(_thread.get());
    }

    ConnectionManager::~ConnectionManager()
    {

    }

    void ConnectionManager::initialize()
    {
        log().debug("initialize()");
        _timer.create(1000, 5000, [this]()
        {
            this->sendStatus();
        });
    }

    void ConnectionManager::sendStatus()
    {
        log().debug("sendStatus()");

        Messages::NodeStatus nodeStatus;
        nodeStatus.set_status("Ok");
        nodeStatus.set_description("none");

        at()->executeWithin(_gateway->at(), [=]
        {
            this->_gateway->sendRaspiMessage(3, nodeStatus);
        });
    }
} } }
