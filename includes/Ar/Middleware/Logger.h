#ifndef Ar_Middleware_Logger_h__
#define Ar_Middleware_Logger_h__

#include <Ar/Middleware/LogFlag.h>
#include <Ar/Middleware/LogLevel.h>

#include <string>
#include <mutex>

namespace Ar { namespace Middleware
{
    class Logger
    {
        class Prologue
        {
        public:
            Prologue();

            explicit Prologue( const std::string &prologue_ );

            std::string prologue;
        };

        class Log
        {
        public:
            Log( LogFlag flag, LogLevel level );
            Log( const std::string &prefix, LogLevel level );

            void setPrologue( const Prologue &prologue );

            const Log& operator()( const char *str, ... ) const;

        private:
            LogFlag     _flag;
            LogLevel    _level;
            Prologue    _prologue;
            const std::string _prefix;

            static std::mutex _mutex;
        };


    public:
        Logger( LogFlag flag, const std::string &prologue = "" );
        Logger( const std::string &prefix, const std::string &prologue = "" );

        void setPrologue( const Prologue &prologue );

        void setPrologue( const std::string &prologue );

        static void setFlag( char flag, char value )
        {
            _logSet[ static_cast< unsigned >( flag ) ] = value;
        }
        
        Log debug;
        Log info;
        Log warning;
        Log error;

    private:
        static char _logSet[ END_LOG_FLAG ];
    };

    typedef Logger LoggingSystem;
} }

#endif // Ar_Middleware_Logger_h__
