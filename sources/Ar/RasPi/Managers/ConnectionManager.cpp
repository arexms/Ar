#include <Ar/RasPi/Managers/ConnectionManager.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Middleware/Utils.h>
#include <Ar/RasPi/Messages/RaspiMessages.pb.h>
#include <Ar/RasPi/RaspiMessagesGateway.h>
#include <Ar/Messages.h>

namespace Ar { namespace RasPi { namespace Managers
{
    ConnectionManager::ConnectionManager(RaspiMessagesGateway *gateway)
        : RaspiManagerIf(Ar::Middleware::CONN_MNGR)
        , _thread(Ar::Middleware::safeNew<Ar::Middleware::ActiveThread>())
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
