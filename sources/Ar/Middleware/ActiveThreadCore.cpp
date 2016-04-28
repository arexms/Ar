#include <Ar/Middleware/ActiveThreadCore.h>
#include <Ar/Middleware/ActiveThread.h>
#include <Ar/Middleware/Utils.h>
#include <iostream>

namespace Ar {
    namespace Middleware
    {
        ActiveThreadCore::ActiveThreadCore(ActiveThread *at)
            : _at(at)
            , _stop(true)
        {
        }

        ActiveThreadCore::~ActiveThreadCore()
        {

        }

        void ActiveThreadCore::start()
        {
            _stop = false;
            _thread = SharedPtr<std::thread>(safeNewWith1Arg<std::thread>([&]() {run(); }));
            log().debug("Core::start() started");
        }

        void ActiveThreadCore::stop()
        {
            if (!_stop)
            {
                _stop = true;
                _thread->join();
                releaseAllMessages();
            }
            log().debug("Core::stop() stopped");
        }

        bool ActiveThreadCore::sendToMe(IMessage *message)
        {
            log().debug("Core::sendToMe() sending");
            return push(message);
        }

        IMessage *ActiveThreadCore::waitFor(MessageId id)
        {
            int i = 0;
            while( i < 20 )
            {
                auto message = find( id );
                if( message != _messages.end())
                {
                    auto ret = *message;
                    _messages.erase(message);
                    return ret;
                }
                boost::this_thread::sleep( boost::posix_time::milliseconds( 100 ) );
                ++i;
            }

            return nullptr;
        }

        void ActiveThreadCore::run()
        {
            while (!_stop)
            {
                IMessage *message = 0;
                {
                    boost::mutex::scoped_lock lock( _mutex );
                    while (_messages.empty() && !_stop)
                    {
                        _condMsg.timed_wait(lock, boost::posix_time::milliseconds( 1000 ));
                        //log().debug("Core::run() idle");
                    }

                    if (_stop)
                    {
                        break;
                    }
                    message = pop();
                }
                dispatch(message);
                
                safeDel(message);
            }
        }

        bool ActiveThreadCore::push(IMessage *message)
        {
            if (_stop) /// @note do not delete message
            {
                return false;
            }

            boost::mutex::scoped_lock lock( _mutex );
            _messages.push_back(message);
            _condMsg.notify_one();

            return true;
        }

        IMessage *ActiveThreadCore::pop()
        {
            auto ret = _messages.front();
            _messages.pop_front();
            return ret;
        }

        bool ActiveThreadCore::dispatch(IMessage *message)
        {
            log().debug("Core::dispatch() dispatching");
            return _at->dispatch(message);
        }

        ActiveThreadCore::Messages::iterator ActiveThreadCore::find(MessageId id)
        {
            boost::mutex::scoped_lock lock( _mutex );
            for(Messages::iterator message = _messages.begin(); message != _messages.end();++message)
            {
                if( (*message)->id() == id )
                {
                    return message;
                }
            }

            return _messages.end();
        }

        void ActiveThreadCore::releaseAllMessages()
        {
            while (!_messages.empty())
            {
                IMessage *message = _messages.front();
                _messages.pop_front();
                safeDel(message);
            }
        }

        Logger& ActiveThreadCore::log()
        {
            return at()->log();
        }
    }
}