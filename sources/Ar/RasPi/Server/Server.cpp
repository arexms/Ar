#include <Ar/RasPi/Server/Server.h>
#include <Ar/RasPi/Server/Protocol.h>

namespace Ar
{
    namespace RasPi
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
