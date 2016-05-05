TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += includes \
    ext/boost_1_60_0

SOURCES += main.cpp \
    sources/Ar/Middleware/ActiveThread.cpp \
    sources/Ar/Middleware/ActiveThreadCore.cpp \
    sources/Ar/Middleware/Logger.cpp \
    sources/Ar/RasPi/Server/Protocol.cpp \
    sources/Ar/RasPi/Server/Server.cpp \
    sources/Ar/RasPi/GpioPin.cpp \
    sources/Ar/RasPi/GpioPinIf.cpp \
    sources/Ar/RasPi/GpioPinImplConsole.cpp \
    sources/Ar/RasPi/GpioPinImplIf.cpp \
    sources/Ar/Udp/UdpRx.cpp \
    sources/Ar/Udp/UdpTrx.cpp \
    sources/Ar/Udp/UdpTx.cpp \
    sources/Ar/Udp/UdpService.cpp \
    sources/Ar/Middleware/ActiveThreadAddresses.cpp \
    sources/Ar/Reset/ResetManager.cpp \
    sources/Ar/Middleware/ActiveObject.cpp \
    sources/Ar/RasPi/Messages/RaspiMessages.pb.cpp \
    sources/Ar/RasPi/Messages/RaspiMessagesSerDes.cpp \
    sources/Ar/RasPi/RaspiMessagesGateway.cpp

HEADERS += \
    includes/Ar/Middleware/ActiveObject.h \
    includes/Ar/Middleware/ActiveThread.h \
    includes/Ar/Middleware/ActiveThreadCore.h \
    includes/Ar/Middleware/LogFlag.h \
    includes/Ar/Middleware/Logger.h \
    includes/Ar/Middleware/LogLevel.h \
    includes/Ar/Middleware/MessageIds.h \
    includes/Ar/Middleware/SharedPtr.h \
    includes/Ar/Middleware/Utils.h \
    includes/Ar/RasPi/Server/Protocol.h \
    includes/Ar/RasPi/Server/ProtocolConfig.h \
    includes/Ar/RasPi/Server/Server.h \
    includes/Ar/RasPi/Server/ServerConfig.h \
    includes/Ar/RasPi/GpioPin.h \
    includes/Ar/RasPi/GpioPinIf.h \
    includes/Ar/RasPi/GpioPinImplConsole.h \
    includes/Ar/RasPi/GpioPinImplIf.h \
    includes/Ar/Udp/UdpRx.h \
    includes/Ar/Udp/UdpRxConfig.h \
    includes/Ar/Udp/UdpTrx.h \
    includes/Ar/Udp/UdpTrxConfig.h \
    includes/Ar/Udp/UdpTx.h \
    includes/Ar/Udp/UdpTxConfig.h \
    includes/Ar/Udp/UdpTypes.h \
    includes/Ar/Common.h \
    includes/Ar/Udp/UdpService.h \
    includes/Ar/Middleware/ActiveThreadAddresses.h \
    includes/Ar/Middleware/Singleton.h \
    includes/Ar/Middleware/IMessage.h \
    includes/Ar/Reset/ResetManager.h \
    includes/Ar/Messages.h \
    includes/Ar/RasPi/Messages/RaspiMessages.pb.h \
    includes/Ar/RasPi/Messages/RaspiMessagesSerDes.h \
    includes/Ar/RasPi/RaspiMessagesGateway.h

LIBS += -L../ArRaspi/ext/boost_1_60_0/stage/lib -lboost_system -lpthread -lprotobuf

DISTFILES += \
    includes/Ar/RasPi/Messages/RaspiMessages.proto
