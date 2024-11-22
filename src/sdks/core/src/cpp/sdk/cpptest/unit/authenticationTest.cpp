#include "unit.h"

class AuthenticationTest : public ::testing::Test
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

TEST_F(AuthenticationTest, Token)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Authentication.token"));

	Firebolt::Authentication::TokenType type = Firebolt::Authentication::TokenType::DEVICE;
	std::optional<Firebolt::Authentication::Options> options;

	auto token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(type, options, &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve token from Authentication.token() method";
	EXPECT_EQ(token.value, expectedValues["value"]);
}

TEST_F(AuthenticationTest, Device)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Authentication.device"));

	std::string device = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve device from Authentication.device() method";
	EXPECT_EQ(device, expectedValues);
}

TEST_F(AuthenticationTest, Session)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Authentication.session"));

	std::string session = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve session from Authentication.session() method";
	EXPECT_EQ(session, expectedValues);
}

TEST_F(AuthenticationTest, Root)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Authentication.root"));

	std::string root = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve root from Authentication.root() method";
	EXPECT_EQ(root, expectedValues);
}