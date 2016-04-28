#ifndef Ar_Udp_UdpTxConfig_h__
#define Ar_Udp_UdpTxConfig_h__

#include <Ar/Udp/UdpTypes.h>

namespace Ar { namespace Udp
{
    struct UdpTxConfig
    {
        Ar::Udp::Ip ip;
        Ar::Udp::Port port;
		bool broadcastEnabled;
    };
} }

#endif // Ar_Udp_UdpTxConfig_h__
