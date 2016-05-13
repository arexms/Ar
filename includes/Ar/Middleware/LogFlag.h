#ifndef Ar_Middleware_LogFlag_h__
#define Ar_Middleware_LogFlag_h__

namespace Ar { namespace Middleware
{
    enum LogFlag
    {
        GENERIC                             = 0x00,
        MIDDLEWARE                          = 0x01,

        UDP_TRX                             = 0x02,
        UDP_TX                              = 0x03,
        UDP_RX                              = 0x04,
        UDPCP_TRX                           = 0x05,
        PIPE                                = 0x06,
        UDP_CP_CONV                         = 0x07,
        MAIN                                = 0x08,
        PRINT_TO_CONSOLE                    = 0x09,
        AT                                  = 0x0A,
        AT_ADDR                             = 0x0B,
        RESET                               = 0x0C,
        UDP_SERVICE                         = 0x0D,
        RASPI_GW                            = 0x0E,
        CONN_MNGR                           = 0x0F,

        END_LOG_FLAG
    };
} }

#endif // Ar_Middleware_LogFlag_h__
