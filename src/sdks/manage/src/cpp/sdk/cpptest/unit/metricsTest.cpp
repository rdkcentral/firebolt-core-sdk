#include "unit.h"

class MetricsTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

TEST_F(MetricsTest, event)
{
    std::string schema = "http://example.com/schema";
    Firebolt::Metrics::EventObject data;
    Firebolt::Error error = Firebolt::Error::None;

    Firebolt::IFireboltAccessor::Instance().MetricsInterface().event(schema, data, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling MetricsInterface.event() method";
}
