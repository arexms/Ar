#include <Ar/RasPi/Server/Protocol.h>

namespace Ar
{
    namespace RasPi
    {
        namespace Server
        {
            Protocol::Protocol()
            {
            }

            Protocol::~Protocol()
            {
            }

            bool Protocol::initialize(const ProtocolConfig &)
            {
                return false;
            }

            void Protocol::run()
            {
            }

            void Protocol::stop()
            {
            }
        }
    }
}
