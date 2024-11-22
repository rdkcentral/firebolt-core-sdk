#include "unit.h"

class SecureStorageTest : public ::testing::Test
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

// Check enum issue with test app verse actual transport
TEST_F(SecureStorageTest, Get)
{
    auto expectedValue = jsonEngine->get_value("SecureStorage.get");

    Firebolt::SecureStorage::StorageScope scope = Firebolt::SecureStorage::StorageScope::DEVICE;

    std::string actualValue = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(scope, "authRefreshToken", &error);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(SecureStorageTest, Set)
{
    // Call setter to set the value
    Firebolt::SecureStorage::StorageScope scope = Firebolt::SecureStorage::StorageScope::DEVICE;
    std::string expectedValue = "123456";
    Firebolt::SecureStorage::StorageOptions options;
    options.ttl = 6.0;
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().set(scope, "authRefreshToken", expectedValue, options, &error);

    // Check if there was an error during the set operation
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to set value in SecureStorage.set() method";
}

TEST_F(SecureStorageTest, Remove)
{
    Firebolt::SecureStorage::StorageScope scope = Firebolt::SecureStorage::StorageScope::DEVICE;
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(scope, "authRefreshToken", &error);

    // Check if there was an error during the remove operation
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to remove value in SecureStorage.remove() method";
}

TEST_F(SecureStorageTest, Clear)
{
    Firebolt::SecureStorage::StorageScope scope = Firebolt::SecureStorage::StorageScope::DEVICE;
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(scope, &error);

    // Check if there was an error during the clear operation
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to clear value in SecureStorage.clear() method";
}
