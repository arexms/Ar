#pragma once
#ifndef Ar_Udp_UdpTx_h__
#define Ar_Udp_UdpTx_h__

#include <Ar/Udp/UdpTxConfig.h>

#include <Ar/Middleware/Logger.h>

#include <boost/asio.hpp>

namespace Ar { namespace Udp
{
    class UdpTx
    {
    public:
        UdpTx();

		~UdpTx();

        bool initialize( const UdpTxConfig &config, boost::asio::ip::udp::socket *socket = 0 );

        bool send( const char *data, unsigned length );

        inline Middleware::Logger& log();

    private:
        UdpTxConfig  _config;
        mutable Middleware::Logger  _logger;
        boost::asio::io_service _io_service;
        boost::asio::ip::udp::socket *_socket;
		bool _socketReceived;
        boost::asio::ip::udp::endpoint _remote_endpoint;
    };

    // IMPLEMENTATION
    inline Middleware::Logger& UdpTx::log()
    {
        return _logger;
    }
} }

#endif // Ar_Udp_UdpTx_h__
