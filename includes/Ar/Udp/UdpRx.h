#pragma once
#ifndef Ar_Udp_UdpRx_h__
#define Ar_Udp_UdpRx_h__

#include <Ar/Udp/UdpRxConfig.h>

#include <Ar/Middleware/Logger.h>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <Ar/Common.h>
#include <functional>

namespace Ar { namespace Udp
{
    typedef std::function<void( DataPtr, unsigned )> HandlerData;

    class UdpRx
    {
    public:
        UdpRx();

        ~UdpRx();

        bool initialize( const UdpRxConfig &config, HandlerData handlerData, boost::asio::ip::udp::socket *socket = 0 );

        void run();

        inline Middleware::Logger& log();

        inline const UdpRxConfig& config() const;

    protected:
        void receivedDatagram( DataPtr data, unsigned length );

        void receivedDatagramAsync( const boost::system::error_code& error, size_t bytes_recvd );

        void startReceive();

    private:
        UdpRxConfig  _config;
        mutable Middleware::Logger  _logger;
        boost::asio::io_service _io_service;
        boost::asio::ip::udp::socket *_socket;
		bool _socketReceived;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        HandlerData _handlerData;
        char *_data;
        boost::thread _rxThread;
		boost::asio::ip::udp::endpoint _local_endpoint;
        bool _stop;
    };

    // IMPLEMENTATION
    inline Middleware::Logger& UdpRx::log()
    {
        return _logger;
    }

    inline const UdpRxConfig& UdpRx::config() const
    {
        return _config;
    }
} }

#endif // Ar_Udp_UdpRx_h__
