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

TEST_F(AccountTest, Id)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Account.id"));

	std::string account_id = Firebolt::IFireboltAccessor::Instance().AccountInterface().id(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve account_id from Account.id() method";
	EXPECT_EQ(account_id, expectedValues);
}

TEST_F(AccountTest, Uid)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Account.uid"));

	std::string account_uid = Firebolt::IFireboltAccessor::Instance().AccountInterface().uid(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve account_uid from Account.uid() method";
	EXPECT_EQ(account_uid, expectedValues);
}