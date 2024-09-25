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

TEST_F(MetricsTest, StartContent)
{

	auto actual_value = jsonEngine->get_value("Metrics.startContent");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent("example", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.startContent() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, StopContent)
{

	auto actual_value = jsonEngine->get_value("Metrics.stopContent");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent("example", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.stopContent() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, Page)
{
	// Parse the expected values from the JSON
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.page"));

	std::string pageId = "xyz";

	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().page(pageId, &error);

	// Compare the expected and actual results
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.page() method";
	EXPECT_EQ(status, expectedValues);
}

TEST_F(MetricsTest, Action)
{
	// Parse the expected values from the JSON
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.action"));
	std::cout << "Expected value for capability " << expectedValues << std::endl;

	Firebolt::Metrics::Category category = Firebolt::Metrics::Category::USER;
	auto type = "The user did foo";
	std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt;

	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().action(category, type, parameters, &error);
	std::cout << "Status value for capability " << status << std::endl;

	// Compare the expected and actual results
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.action() method";
	EXPECT_EQ(status, expectedValues);
}

TEST_F(MetricsTest, Error)
{
	// Parse the expected values from the JSON
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.error"));
	std::cout << "Expected value for capability " << expectedValues << std::endl;

	Firebolt::Metrics::ErrorType type = Firebolt::Metrics::ErrorType::MEDIA;
	std::string code = "MEDIA-STALLED";
	std::string description = "playback stalled";
	std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt;
	bool visible = true;

	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().error(type, code, description, visible, parameters, &error);
	std::cout << "Status value for capability " << status << std::endl;

	// Compare the expected and actual results
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.error() method";
	EXPECT_EQ(status, expectedValues);
}

TEST_F(MetricsTest, MediaLoadStart)
{
	auto actual_value = jsonEngine->get_value("Metrics.mediaLoadStart");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaLoadStart("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaLoadStart() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaPlay)
{
	auto actual_value = jsonEngine->get_value("Metrics.mediaPlay");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlay("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaPlay() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaPlaying)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaPlaying");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlaying("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaPlaying() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaPause)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaPause");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPause("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaPause() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaWaiting)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaWaiting");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaWaiting("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaWaiting() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaProgress)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaProgress");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaProgress("345", "0.75", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaProgress() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaSeeking)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaSeeking");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaSeeking("345", "0.25", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaSeeking() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaSeeked)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaSeeked");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaSeeked("345", "0.51", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaSeeked() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaRateChange)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaRateChange");

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRateChange("345", 2, &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaRateChange() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaRenditionChange)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaRenditionChange");
	std::optional<std::string> profile = std::nullopt;

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRenditionChange("345", 1080, 950, 1020, profile, &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Metrics.mediaRenditionChange() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MediaEnded)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaEnded");
	std::optional<std::string> profile = std::nullopt;

	auto status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaEnded("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve account_uid from Metrics.mediaEnded() method";
	EXPECT_EQ(status, STRING_TO_BOOL(actual_value));
}
