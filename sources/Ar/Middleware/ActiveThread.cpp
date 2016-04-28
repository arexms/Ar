#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Middleware/Utils.h>
#include <Ar/Middleware/ActiveThreadAddresses.h>

namespace Ar {
    namespace Middleware
    {
        ActiveThread::ActiveThread()
            : _log(AT)
        {
        }

        ActiveThread::~ActiveThread()
        {
            stop();
            //_log.warning("END");
        }

        void ActiveThread::start(const std::string &name)
        {
            _name = name;
            log().setPrologue(this->name()+": ");

            _core = SharedPtr<ActiveThreadCore>(safeNewWith1Arg<ActiveThreadCore, ActiveThread*>(this));
            _core->start();
            ActiveThreadAddresses::getInstance().add(this->name(), this);
            log().debug("start() started");
        }

        void ActiveThread::stop()
        {
            log().debug("stop() stopping");
            ActiveThreadAddresses::getInstance().remove(this->name());
            _core->stop();
        }

        void ActiveThread::sendToMe(IMessage *message)
        {
            _core->sendToMe(message);
        }

        bool ActiveThread::sendTo(const std::string &atName, IMessage *message)
        {
            auto to = ActiveThreadAddresses::getInstance().get(atName);
            if(to!=nullptr)
            {
                sendTo(to, message);
                return true;
            }

            log().warning("sendTo() Receiver '%s not found!", atName.c_str());
            return false;
        }

        bool ActiveThread::sendTo(ActiveThread *at, IMessage *message)
        {
            message->from = this;
            message->to = at;
            message->to->sendToMe(message);
            return true;
        }

        bool ActiveThread::dispatch(IMessage *message)
        {
            log().debug("dispatch() received %i", message->id());
            auto receiver = _receivers.find(message->id());

            if (receiver != _receivers.end())
            {
                receiver->second->execute(message);
                return true;
            }

            log().info("dispatch() No registered receiver for %i!", message->id());
            return false;
        }
    }
}
