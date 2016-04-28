#include <Ar/Udp/UdpTrx.h>

#include <Ar/Udp/UdpTx.h>
#include <Ar/Udp/UdpRx.h>

#include <Ar/Middleware/Utils.h>

namespace Ar { namespace Udp
{
    UdpTrx::UdpTrx()
        : _tx( 0 )
        , _rx( 0 )
        , _logger( Middleware::UDP_TRX )
        , _socket( 0 )
        , _rxThread( 0 )
    {}

    UdpTrx::~UdpTrx()
    {
        Middleware::safeDel( _tx );
        Middleware::safeDel( _rx );

        if( _config.useCommonSocket )
        {
            _io_service.stop();
            Middleware::safeDel( _socket );
        }
        if(_rxThread)
        {
            _rxThread->join();
            delete _rxThread;
        }
    }

    bool UdpTrx::initialize( const UdpTrxConfig &config_, HandlerData handlerData )
    {
        _config = config_;
        Middleware::safeNew( _tx );
        Middleware::safeNew( _rx );

        if( config().useCommonSocket )
        {
            Middleware::safeNewWith1Arg( _socket, _io_service );
            _socket->open( boost::asio::ip::udp::v4() );
        }

        auto txInit = _tx->initialize( config().tx, _socket );
        auto rxInit = _rx->initialize( config().rx, handlerData, _socket );

        if(txInit && rxInit)
        {
            log().info( "UdpTrx::initialize() ok" );
            return true;
        }
        else
        {
            log().error( "UdpTrx::initialize() failed!" );
            return false;
        }
    }

    void UdpTrx::run()
    {
        log().debug( "UdpTrx::run" );
        _rxThread = new std::thread( [&](){_rx->run();} );
    }

    void UdpTrx::send( DataPtr data, unsigned length )
    {
        log().debug( "UdpTrx::send() ... " );
        sendData( data.get(), length );
    }

    bool UdpTrx::sendData( const char *data, unsigned length ) const
    {
        char *buff = Middleware::safeNewArray< char >( length + 1 );
        memcpy(buff, data, length );
        buff[ length ] = '\0';
        _tx->send( buff, length );
        log().debug( "UdpTrx::send length %u", length );

        return true;
    }
} }
