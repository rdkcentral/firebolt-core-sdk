#include "unit.h"

class AccountTest : public ::testing::Test
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

TEST_F(AccountTest, session)
{
    std::string token = "expiresIn";
    int32_t expiresIn = 84000;
    Firebolt::IFireboltAccessor::Instance().AccountInterface().session(token, expiresIn, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AccountInterface.session() method";
}
