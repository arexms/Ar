#include <gtest/gtest.h>

#include <Ar/Messages.h>
#include <Ar/Middleware/ActiveThread.h>

namespace Ar
{
    class MessagesTest : public testing::Test
    {
    public:
        MessagesTest()
        {
            from = new Middleware::ActiveThread();
            to = new Middleware::ActiveThread();
        }

        virtual ~MessagesTest()
        {
            delete from;
            delete to;
        }

        Middleware::ActiveThread *from;
        Middleware::ActiveThread *to;
    };

    TEST_F(MessagesTest, CheckIfIMessageCorrectlyCreatesResponse)
    {
        ResetMessage rm;
        rm.from = from;
        rm.to = to;

        auto resp = rm.createResponse();


        EXPECT_EQ(to, resp->from);
        EXPECT_EQ(from, resp->to);

        delete resp;
    }

    TEST_F(MessagesTest, CheckCorrectnessOfResetMessage)
    {
        ResetMessage rm;
        rm.from = from;
        rm.to = to;

        auto resp = rm.createResponse();

        EXPECT_EQ(Middleware::MessageId::RESET, rm.id());
        EXPECT_EQ(Middleware::MessageId::RESET, ResetMessage::MSG_ID());

        EXPECT_EQ(Middleware::MessageId::RESET_RESPONSE, resp->id());
        EXPECT_EQ(Middleware::MessageId::RESET_RESPONSE, ResetMessage::Response::MSG_ID());

        delete resp;
    }

    TEST_F(MessagesTest, CheckCorrectnessOfAddUdpTrxRouteMessage)
    {
        AddUdpTrxRouteMessage rm;
        rm.from = from;
        rm.to = to;

        auto resp = rm.createResponse();

        EXPECT_EQ(Middleware::MessageId::ADD_UDP_TRX_ROUTE, rm.id());
        EXPECT_EQ(Middleware::MessageId::ADD_UDP_TRX_ROUTE, AddUdpTrxRouteMessage::MSG_ID());

        EXPECT_EQ(Middleware::MessageId::ADD_UDP_TRX_ROUTE_RESPONSE, resp->id());
        EXPECT_EQ(Middleware::MessageId::ADD_UDP_TRX_ROUTE_RESPONSE, AddUdpTrxRouteMessage::Response::MSG_ID());

        delete resp;
    }

    TEST_F(MessagesTest, CheckCorrectnessOfUdpPacketMessage)
    {
        UdpPacketMessage rm;
        rm.from = from;
        rm.to = to;

        auto resp = rm.createResponse();

        EXPECT_EQ(Middleware::MessageId::UDP_PACKET, rm.id());
        EXPECT_EQ(Middleware::MessageId::UDP_PACKET, UdpPacketMessage::MSG_ID());

        EXPECT_EQ(Middleware::MessageId::UDP_PACKET_RESPONSE, resp->id());
        EXPECT_EQ(Middleware::MessageId::UDP_PACKET_RESPONSE, UdpPacketMessage::Response::MSG_ID());

        delete resp;
    }
}


