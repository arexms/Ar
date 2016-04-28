#ifndef Ar_Udp_UdpTrxConfig_h__
#define Ar_Udp_UdpTrxConfig_h__

#include <Ar/Udp/UdpRxConfig.h>
#include <Ar/Udp/UdpTxConfig.h>

namespace Ar { namespace Udp
{
    struct UdpTrxConfig
    {
		bool useCommonSocket;
        UdpRxConfig rx;
        UdpTxConfig tx;
    };
} }

#endif // Ar_Udp_UdpTrxConfig_h__
