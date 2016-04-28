#ifndef Ar_Udp_UdpRxConfig_h__
#define Ar_Udp_UdpRxConfig_h__

#include <Ar/Udp/UdpTypes.h>

namespace Ar { namespace Udp
{
    struct UdpRxConfig
    {
        Ar::Udp::Ip ip;
        Ar::Udp::Port port;
        unsigned maxDataSize;
		bool use_INADDR_ANY;
    };
} }

#endif // Ar_Udp_UdpRxConfig_h__
