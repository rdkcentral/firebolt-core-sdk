#include "unit.h"

class SecureStorageTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::SecureStorage::StorageScope scope;
    std::string appId = "exampleAppId";

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

TEST_F(SecureStorageTest, clearForApp)
{
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clearForApp(appId, scope, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling SecureStorageInterface.clearForApp() method";
}

TEST_F(SecureStorageTest, removeForApp)
{
    std::string key = "exampleKey";

    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().removeForApp(appId, scope, key, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling SecureStorageInterface.removeForApp() method";
}

TEST_F(SecureStorageTest, setForApp)
{
    std::string key = "exampleKey";
    std::string value = "exampleValue";
    std::optional<Firebolt::SecureStorage::StorageOptions> options = std::nullopt;

    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().setForApp(appId, scope, key, value, options, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling SecureStorageInterface.setForApp() method";
}
