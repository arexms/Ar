#include <Ar/Raspi/Server/Server.h>
#include <Ar/Raspi/Server/Protocol.h>

namespace Ar
{
    namespace Raspi
    {
        namespace Server
        {
            Server::Server()
                : _protocol(new Protocol())
            {
            }

            Server::~Server()
            {
            }

            bool Server::initialize(const ServerConfig &)
            {
                return false;
            }

            void Server::run()
            {
            }

            void Server::stop()
            {
            }
        }
    }
}
