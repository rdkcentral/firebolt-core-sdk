#include "unit.h"

class LifecycleTest : public ::testing::Test
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

TEST_F(LifecycleTest, Close)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Lifecycle.close"));

	Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(Firebolt::Lifecycle::CloseReason::USER_EXIT, &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling Lifecycle.close() method";
}
