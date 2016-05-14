TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += includes \
    ext/boost_1_60_0

SOURCES += main.cpp \
    sources/Ar/Udp/UdpRx.cpp \
    sources/Ar/Udp/UdpService.cpp \
    sources/Ar/Udp/UdpTrx.cpp \
    sources/Ar/Udp/UdpTx.cpp \
    sources/Ar/Middleware/ActiveObject.cpp \
    sources/Ar/Middleware/ActiveThread.cpp \
    sources/Ar/Middleware/ActiveThreadAddresses.cpp \
    sources/Ar/Middleware/ActiveThreadCore.cpp \
    sources/Ar/Middleware/Logger.cpp \
    sources/Ar/Middleware/Timer.cpp \
    sources/Ar/Raspi/Managers/ConnectionManager.cpp \
    sources/Ar/Raspi/Managers/RaspiManagerIf.cpp \
    sources/Ar/Raspi/Messages/RaspiMessageBuilder.cpp \
    sources/Ar/Raspi/Messages/RaspiMessages.pb.cpp \
    sources/Ar/Raspi/Messages/RaspiMessagesSerDes.cpp \
    sources/Ar/Raspi/Server/Protocol.cpp \
    sources/Ar/Raspi/Server/Server.cpp \
    sources/Ar/Raspi/GpioPin.cpp \
    sources/Ar/Raspi/GpioPinIf.cpp \
    sources/Ar/Raspi/GpioPinImplConsole.cpp \
    sources/Ar/Raspi/GpioPinImplIf.cpp \
    sources/Ar/Raspi/RaspiMessagesGateway.cpp \
    sources/Ar/Reset/ResetManager.cpp

HEADERS += \
    includes/Ar/Udp/UdpRx.h \
    includes/Ar/Udp/UdpRxConfig.h \
    includes/Ar/Udp/UdpTrx.h \
    includes/Ar/Udp/UdpTrxConfig.h \
    includes/Ar/Udp/UdpTx.h \
    includes/Ar/Udp/UdpTxConfig.h \
    includes/Ar/Udp/UdpTypes.h \
    includes/Ar/Common.h \
    includes/Ar/Udp/UdpService.h \
    includes/Ar/Messages.h \
    includes/Ar/Middleware/ActiveObject.h \
    includes/Ar/Middleware/ActiveThread.h \
    includes/Ar/Middleware/ActiveThreadAddresses.h \
    includes/Ar/Middleware/ActiveThreadCore.h \
    includes/Ar/Middleware/IMessage.h \
    includes/Ar/Middleware/LogFlag.h \
    includes/Ar/Middleware/Logger.h \
    includes/Ar/Middleware/LogLevel.h \
    includes/Ar/Middleware/MessageIds.h \
    includes/Ar/Middleware/SharedPtr.h \
    includes/Ar/Middleware/Singleton.h \
    includes/Ar/Middleware/Timer.h \
    includes/Ar/Middleware/Utils.h \
    includes/Ar/Raspi/Managers/ConnectionManager.h \
    includes/Ar/Raspi/Managers/RaspiManagerIf.h \
    includes/Ar/Raspi/Messages/RaspiMessage.h \
    includes/Ar/Raspi/Messages/RaspiMessageBuilder.h \
    includes/Ar/Raspi/Messages/RaspiMessages.pb.h \
    includes/Ar/Raspi/Messages/RaspiMessagesSerDes.h \
    includes/Ar/Raspi/Server/Protocol.h \
    includes/Ar/Raspi/Server/ProtocolConfig.h \
    includes/Ar/Raspi/Server/Server.h \
    includes/Ar/Raspi/Server/ServerConfig.h \
    includes/Ar/Raspi/GpioPin.h \
    includes/Ar/Raspi/GpioPinIf.h \
    includes/Ar/Raspi/GpioPinImplConsole.h \
    includes/Ar/Raspi/GpioPinImplIf.h \
    includes/Ar/Raspi/RaspiMessagesGateway.h \
    includes/Ar/Reset/ResetManager.h

    includes/Ar/Middleware/Timer.h

LIBS += -L../ArRaspi/ext/boost_1_60_0/stage/lib -lboost_system -lpthread -lprotobuf

DISTFILES += \
    includes/Ar/Raspi/Messages/RaspiMessages.proto
