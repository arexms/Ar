#pragma once

#include <Ar/RasPi/Server/ServerConfig.h>
#include <Ar/Middleware/SharedPtr.h>

namespace Ar
{
    namespace RasPi
    {
        namespace Server
        {
            class Protocol;

            class Server
            {
            public:
                Server();
                ~Server();

                bool initialize(const ServerConfig &config);
                void run();
                void stop();

            protected:
                const ServerConfig& config() const;
                Ar::Middleware::SharedPtr<Protocol> protocol();

            private:
                ServerConfig _config;
                Ar::Middleware::SharedPtr<Protocol> _protocol;
            };

            // IMPLEMENTATION
            inline const ServerConfig& Server::config() const
            {
                return _config;
            }

            inline Ar::Middleware::SharedPtr<Protocol> Server::protocol()
            {
                return _protocol;
            }
        }
    }
}
