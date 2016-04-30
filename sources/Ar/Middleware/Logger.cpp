#include <Ar/Middleware/Logger.h>

#include <cstdarg>

#include <chrono>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>

namespace Ar { namespace Middleware
{
    static const char *LogFlagStr[] =
    {
        "    GENERIC",                      //  0x00
        " MIDDLEWARE",                      //  0x01
        "    UDP_TRX",                      //  0x02
        "     UDP_TX",                      //  0x03
        "     UDP_RX",                      //  0x04
        "  UDPCP_TRX",                      //  0x05
        "       PIPE",                      //  0x06
        "UDP_CP_CONV",                      //  0x07
        "       MAIN",                      //  0x08
        "           ",                      //  0x09
        "         AT",                      //  0x0A
        "    AT_ADDR",                      //  0x0B
        "      RESET",                      //  0x0C
        "UDP_SERVICE",                      //  0x0D

        "NONE"
    };
    
    static const char *LogLevelStr[] =
    {
        "ERR",
        "WRN",
        "INF",
        "DBG",
        "???"
    };
    
    std::mutex Logger::Log::_mutex;
    char Logger::_logSet[ END_LOG_FLAG ] = { 0 };

    Logger::Prologue::Prologue()
    {}

    Logger::Prologue::Prologue( const std::string &prologue_ )
        : prologue( prologue_ )
    {}

    Logger::Log::Log( LogFlag flag, LogLevel level )
        : _flag( flag)
        , _level( level )
    {}

    void Logger::Log::setPrologue( const Prologue &prologue )
    {
        _prologue = prologue;
    }

    const Logger::Log& Logger::Log::operator()( const char *str, ... ) const
    {
        std::unique_lock<std::mutex> lock( _mutex );
        //if( Logger::_logSet[ _flag ] < _level ) return *this;
        //std::string now = boost::posix_time::to_simple_string( boost::posix_time::microsec_clock::local_time() );

            auto now_ = std::chrono::high_resolution_clock::now();
            auto in_time_t = std::chrono::high_resolution_clock::to_time_t(now_);

                auto mc_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(now_.time_since_epoch());
                auto mc = mc_since_epoch.count() % 1000000;

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << ":" << mc;
            std::string now = ss.str();

        std::string	temp = std::string( "[" ) + now + "][" + LogLevelStr[ _level ] + "][" + LogFlagStr[ _flag ] + "]" + " " + _prologue.prologue + str + "\n";

        char buff[ 2048 ] = {0};
        va_list args;
        va_start( args, str );
        vsprintf( buff, temp.c_str(), args );
        va_end( args );
        //if( Logger::_logSet[ PRINT_TO_CONSOLE ] || _level == ERROR )
        {
            printf( "%s", buff );
        }
        
        std::fstream file;
        file.open( "logs.txt", std::fstream::app );
        file.write( buff, std::strlen( buff ) );
        file.close();
        
        return *this;
    }

    Logger::Logger( LogFlag flag, const std::string &prologue )
        : debug( flag, DEBUG )
        , info( flag, INFO )
        , warning( flag, WARNING )
        , error( flag, ERROR )
    {
        setPrologue( prologue );
    }

    void Logger::setPrologue( const Prologue &prologue )
    {
        debug.setPrologue( prologue );
        info.setPrologue( prologue );
        warning.setPrologue( prologue );
        error.setPrologue( prologue );
    }

    void Logger::setPrologue( const std::string &prologue )
    {
        Prologue pr( prologue );
        setPrologue( pr );
    }
} }
