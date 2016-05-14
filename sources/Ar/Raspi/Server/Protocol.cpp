#include <Ar/Raspi/Server/Protocol.h>

namespace Ar
{
    namespace Raspi
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
