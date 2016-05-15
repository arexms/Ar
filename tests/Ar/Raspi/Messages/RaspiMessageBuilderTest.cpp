#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Ar/Raspi/Messages/RaspiMessageBuilder.h>

using ::testing::Return;
using ::testing::_;

namespace Ar { namespace Raspi { namespace Messages
{
    class RaspiMessageBuilderTest : public testing::Test
    {
    public:
        RaspiMessageHeaderBuilder _headerBuilder;
        RaspiMessageBodyBuilder _bodyBuilder;
        RaspiMessageEnvelopeBuilder _envelopeBuilder;
    };

    class MockRaspiMessageHeaderBuilder : public RaspiMessageHeaderBuilder
    {
    public:

        MOCK_METHOD1( build, bool(RaspiMessageEnvelope &) );
    };

    class MockRaspiMessageBodyBuilder : public RaspiMessageBodyBuilder
    {
    public:

        MOCK_METHOD1( build, bool(RaspiMessageEnvelope &) );
    };

    class MockReset : public Reset
    {
    public:
        MOCK_CONST_METHOD1(SerializeToString, bool(std::string* output));
    };

    TEST_F(RaspiMessageBuilderTest, CheckCorrectnessOfHeaderBuilder)
    {
        RaspiMessageEnvelope envelope;

        _headerBuilder
                .setInterfaceVersion("iv_test")
                .setFrom("from_test")
                .setTo("to_test");

        EXPECT_TRUE(_headerBuilder.build(envelope));

        EXPECT_EQ(envelope.header().interfaceversion(), "iv_test");
        EXPECT_EQ(envelope.header().from(), "from_test");
        EXPECT_EQ(envelope.header().to(), "to_test");
        EXPECT_EQ(envelope.header().id(), 0);

        /// @note Check wether id incresed by 1
        _headerBuilder.build(envelope);
        EXPECT_EQ(envelope.header().id(), 1);
    }

    TEST_F(RaspiMessageBuilderTest, CheckCorrectnessOfBodyBuilder)
    {
        RaspiMessageEnvelope envelope;
        Reset reset;

        _bodyBuilder.setMessageAndType(99, &reset);

        EXPECT_TRUE(_bodyBuilder.build(envelope));

        EXPECT_EQ(envelope.body().type(), 99);
    }

    /*TEST_F(RaspiMessageBuilderTest, CheckBodyBuilderIfMessageSerializationFails)
    {
        RaspiMessageEnvelope envelope;
        MockReset mockReset;

        EXPECT_CALL(mockReset, SerializeToString(_))
                .WillOnce(Return(false));

        _bodyBuilder.setMessageAndType(99, &mockReset);

        EXPECT_FALSE(_bodyBuilder.build(envelope));
        EXPECT_EQ(envelope.body().type(), 99);
    }*/

    TEST_F(RaspiMessageBuilderTest, CheckCorrectnessOfEnvelopeBuilder)
    {
        RaspiMessageEnvelope envelope;
        Reset reset;
        MockRaspiMessageHeaderBuilder mockRaspiMessageHeaderBuilder;
        MockRaspiMessageBodyBuilder mockRaspiMessageBodyBuilder;

        _envelopeBuilder
                .setHeaderBuilder(&mockRaspiMessageHeaderBuilder)
                .setBodyBuilder(&mockRaspiMessageBodyBuilder);

        EXPECT_CALL(mockRaspiMessageHeaderBuilder, build(_))
                .WillOnce(Return(true));

        EXPECT_CALL(mockRaspiMessageBodyBuilder, build(_))
                .WillOnce(Return(true));

        EXPECT_TRUE(_envelopeBuilder.build(envelope));
    }

    TEST_F(RaspiMessageBuilderTest, CheckBehaviourIfHeaderBuilderFails)
    {
        RaspiMessageEnvelope envelope;
        Reset reset;
        MockRaspiMessageHeaderBuilder mockRaspiMessageHeaderBuilder;
        MockRaspiMessageBodyBuilder mockRaspiMessageBodyBuilder;

        _envelopeBuilder
                .setHeaderBuilder(&mockRaspiMessageHeaderBuilder)
                .setBodyBuilder(&mockRaspiMessageBodyBuilder);

        EXPECT_CALL(mockRaspiMessageHeaderBuilder, build(_))
                .WillOnce(Return(false));

        EXPECT_CALL(mockRaspiMessageBodyBuilder, build(_))
                .Times(0); /// @note Times 0 because it should not be called if header fails.

        EXPECT_FALSE(_envelopeBuilder.build(envelope));
    }

    TEST_F(RaspiMessageBuilderTest, CheckBehaviourIfBodyBuilderFails)
    {
        RaspiMessageEnvelope envelope;
        Reset reset;
        MockRaspiMessageHeaderBuilder mockRaspiMessageHeaderBuilder;
        MockRaspiMessageBodyBuilder mockRaspiMessageBodyBuilder;

        _envelopeBuilder
                .setHeaderBuilder(&mockRaspiMessageHeaderBuilder)
                .setBodyBuilder(&mockRaspiMessageBodyBuilder);

        EXPECT_CALL(mockRaspiMessageHeaderBuilder, build(_))
                .WillOnce(Return(true));

        EXPECT_CALL(mockRaspiMessageBodyBuilder, build(_))
                .WillOnce(Return(false));

        EXPECT_FALSE(_envelopeBuilder.build(envelope));
    }

} } }
