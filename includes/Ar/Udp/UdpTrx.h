#pragma once
#ifndef Ar_Udp_UdpTrx_h__
#define Ar_Udp_UdpTrx_h__

#include <Ar/Udp/UdpTrxConfig.h>

#include <Ar/Middleware/Logger.h>

#include <Ar/Common.h>

#include <boost/asio.hpp>
#include <thread>

namespace Ar { namespace Udp
{
    class UdpTx;
    class UdpRx;

    class UdpTrx
    {
    public:
        UdpTrx();

        ~UdpTrx();

        bool initialize( const UdpTrxConfig &config_, std::function<void( DataPtr, unsigned )> handlerData );

        void run();

        void send( DataPtr data, unsigned length );

        bool sendData( const char *data, unsigned length ) const;

        inline const UdpTrxConfig& config() const;

        inline Middleware::Logger& log() const;

    private:
        UdpTrxConfig				_config;
        UdpTx                       *_tx;
        UdpRx                       *_rx;
        mutable Middleware::Logger  _logger;
		boost::asio::ip::udp::socket *_socket;
        boost::asio::io_service		_io_service;
        std::thread                 *_rxThread;
    };

    // IMPLEMENTATION
    inline const UdpTrxConfig& UdpTrx::config() const
    {
        return _config;
    }

    inline Middleware::Logger& UdpTrx::log() const
    {
        return _logger;
    }
} }

#endif // Ar_Udp_UdpTrx_h__
