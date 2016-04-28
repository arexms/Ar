#include <Ar/Udp/UdpTx.h>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include <Ar/Middleware/Utils.h>

#include <sstream>

using boost::asio::ip::udp;

namespace Ar { namespace Udp
{
    UdpTx::UdpTx()
        : _logger( Middleware::UDP_TX, "UdpTx::" ) 
        , _socket( 0 )
        , _socketReceived( true )
    {}

    UdpTx::~UdpTx()
    {
        if( ! _socketReceived )
        {
            Middleware::safeDel( _socket );
        }
    }

    bool UdpTx::initialize(const UdpTxConfig &config, boost::asio::ip::udp::socket *socket )
    {
        _config = config;
        _socket = socket;

        if( ! _socket )
        {
            Middleware::safeNewWith1Arg( _socket, _io_service );
            _socket->open( boost::asio::ip::udp::v4() );
            _socketReceived = false;
        }

        if( _config.broadcastEnabled )
        {
            boost::asio::socket_base::broadcast option( true );
            _socket->set_option( option );
        }
   
        _remote_endpoint = boost::asio::ip::udp::endpoint( boost::asio::ip::address::from_string( _config.ip.c_str() ), _config.port );

        std::stringstream ss;
        ss << _remote_endpoint;

        log().info( "initialize() initialized: %s", ss.str().c_str() );

        return true;
    }

    bool UdpTx::send( const char *data, unsigned length )
    {
        boost::system::error_code ignored_error;
        _socket->send_to(boost::asio::buffer(data, length), _remote_endpoint, 0, ignored_error);
        log().debug( "send() length %u", length );
        /// @todo use shared_ptr
        Middleware::safeDelArray( data );

        return true;
    }
} }
