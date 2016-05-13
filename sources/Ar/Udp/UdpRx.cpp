#include <Ar/Udp/UdpRx.h>

#include <functional>
#include <Ar/Middleware/Utils.h>

#include <sstream>

using boost::asio::ip::udp;

namespace Ar { namespace Udp
{
    UdpRx::UdpRx()
        : _logger( Middleware::UDP_RX, "UdpRx::" )
        , _socket( nullptr )
        , _socketReceived( true )
        , _data( nullptr )
        , _rxThread( nullptr )
        , _stop( false )
    {}

    UdpRx::~UdpRx()
    {
        _stop = true;
        _socket->cancel();
        _io_service.stop();
        if( ! _socketReceived )
        {
            Middleware::safeDel( _socket );
        }

        if(_rxThread)
        {
            _rxThread->join();
            Middleware::safeDel(_rxThread);
        }
        Middleware::safeDelArray( _data );

        log().debug( "~UdpRx() stopped" );
    }

    bool UdpRx::initialize(const UdpRxConfig &config_, HandlerData handlerData, boost::asio::ip::udp::socket *socket )
    {
        _config = config_;
        _socket = socket;
        _handlerData = handlerData;

        if( ! _socket )
        {
            Middleware::safeNewWith1Arg( _socket, _io_service );
            _socket->open( boost::asio::ip::udp::v4() );
            _socketReceived = false;
        }

        Middleware::safeNewArray( _data, config().maxDataSize );
        _local_endpoint.port( config().port );

        /// @note Default addres is INADDR_ANY so...
        if( ! config().use_INADDR_ANY )
        {
            _local_endpoint.address( boost::asio::ip::address::from_string( config().ip ) );
        }

        std::stringstream ss;
        ss << _local_endpoint;
        
        boost::system::error_code ec;
        _socket->bind( _local_endpoint, ec );

        if(ec)
        {
            log().error( "initialize() ERROR: (%s) %s", ss.str().c_str(), ec.message().c_str() );
            return false;
        }

        log().info( "initialize() initialized: %s, maxDataSize=%u", ss.str().c_str(), config().maxDataSize );
        return true;
    }

    void UdpRx::run()
    {
        log().debug( "run()" );
        startReceive();

        /// @note static_cast<size_t (boost::asio::io_service::*)()> because of 2 implementation of method run (with and without args)
        _rxThread = new std::thread (
                        std::bind( static_cast<size_t (boost::asio::io_service::*)()>(&boost::asio::io_service::run), &_socket->get_io_service() )
                    );
    }

    void UdpRx::startReceive()
    {
        log().debug( "startReceive()" );
        _socket->async_receive_from(
            boost::asio::buffer( _data, config().maxDataSize ), _local_endpoint,
            std::bind(&UdpRx::receivedDatagramAsync, this,
              std::placeholders::_1/*boost::asio::placeholders::error*/,
              std::placeholders::_2/*boost::asio::placeholders::bytes_transferred*/));
    }

    void UdpRx::receivedDatagramAsync( const boost::system::error_code& error, size_t length )
    {
        std::stringstream ss;
        ss << _local_endpoint;
        log().debug( "receivedDatagramAsync() length %d, (%s)", length, ss.str().c_str() );

        if( ! error || error == boost::asio::error::message_size )
        {
            char *data_ = Middleware::safeNewArray< char >( length + 1 );
            memcpy(data_, _data, length );
            data_[ length ] = '\0';
        
            DataPtr data( data_ );
            unsigned l = static_cast< unsigned >( length );

            _handlerData( data, l );
        }
        else
        {
            log().error( "receivedDatagramAsync() Receiving failed: %s", error.message().c_str() );
        }

        if( ! _stop )
        {
            startReceive();
        }
    }
} }
