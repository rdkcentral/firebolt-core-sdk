#include "unit.h"

class ParametersTest : public ::testing::Test
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

TEST_F(ParametersTest, Initialization)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Parameters.initialization"));

	Firebolt::Parameters::AppInitialization appInitialization = Firebolt::IFireboltAccessor::Instance().ParametersInterface().initialization(&error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve appInitialization from Parameters.initialization() method";
	EXPECT_EQ(appInitialization.us_privacy, expectedValues["us_privacy"]);
	EXPECT_EQ(appInitialization.lmt, expectedValues["lmt"]);

	nlohmann::json_abi_v3_11_3::json navigateTo = nlohmann::json::parse(appInitialization.discovery.value().navigateTo.value());

	EXPECT_EQ(navigateTo["action"],
			  expectedValues["discovery"]["navigateTo"]["action"]);
	EXPECT_EQ(navigateTo["context"]["source"],
			  expectedValues["discovery"]["navigateTo"]["context"]["source"]);
	EXPECT_EQ(navigateTo["data"]["entityId"],
			  expectedValues["discovery"]["navigateTo"]["data"]["entityId"]);
	EXPECT_EQ(navigateTo["data"]["entityType"],
			  expectedValues["discovery"]["navigateTo"]["data"]["entityType"]);
	EXPECT_EQ(navigateTo["data"]["programType"],
			  expectedValues["discovery"]["navigateTo"]["data"]["programType"]);
}