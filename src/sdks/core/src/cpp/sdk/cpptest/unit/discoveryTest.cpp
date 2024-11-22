#include "unit.h"

class DiscoveryTest : public ::testing::Test 
{
protected:
	JsonEngine* jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
	
    void SetUp() override
	{
		jsonEngine = new JsonEngine();
	}

	void TearDown() override
	{
		delete jsonEngine;
	}

	// Helper function to mock EntityInfo
    Firebolt::Entertainment::EntityInfo mockEntityInfo()
    {
        Firebolt::Entertainment::EntityInfo entityInfo;
        entityInfo.identifiers.entityId = "345";
        entityInfo.title = "Cool Runnings";
        entityInfo.entityType = Firebolt::Entertainment::EntityInfoEntityType::PROGRAM;
        entityInfo.programType = Firebolt::Entertainment::ProgramType::MOVIE;
        entityInfo.synopsis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.";
        entityInfo.releaseDate = "1993-01-01T00:00:00.000Z";

        // Mock content ratings
        Firebolt::Entertainment::ContentRating usRating;
        usRating.scheme = Firebolt::Entertainment::ContentRatingScheme::US_MOVIE;
        usRating.rating = "PG";

        Firebolt::Entertainment::ContentRating caRating;
        caRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_MOVIE;
        caRating.rating = "G";

        entityInfo.contentRatings = std::vector<Firebolt::Entertainment::ContentRating>{usRating, caRating};

        // Mock ways to watch
        Firebolt::Entertainment::WayToWatch wayToWatch;
        wayToWatch.identifiers.assetId = "123";
        wayToWatch.expires = "2025-01-01T00:00:00.000Z";
        wayToWatch.entitled = true;
        wayToWatch.entitledExpires = "2025-01-01T00:00:00.000Z";
        wayToWatch.offeringType = Firebolt::Entertainment::OfferingType::BUY;
        wayToWatch.price = 2.99f;

        wayToWatch.videoQuality = std::vector<Firebolt::Entertainment::WayToWatchVideoQuality>{Firebolt::Entertainment::WayToWatchVideoQuality::UHD};
        wayToWatch.audioProfile = std::vector<Firebolt::Types::AudioProfile>{Firebolt::Types::AudioProfile::DOLBY_ATMOS};
        wayToWatch.audioLanguages = std::vector<std::string>{"en"};
        wayToWatch.closedCaptions = std::vector<std::string>{"en"};
        wayToWatch.subtitles = std::vector<std::string>{"es"};
        wayToWatch.audioDescriptions = std::vector<std::string>{"en"};

        entityInfo.waysToWatch = std::vector<Firebolt::Entertainment::WayToWatch>{wayToWatch};

        return entityInfo;
    }
};


TEST_F(DiscoveryTest, Policy)
{
	Firebolt::Error error = Firebolt::Error::None;
	
	// Parsing expected JSON values into a BooleanMap
	nlohmann::json_abi_v3_11_3::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Discovery.policy"));
	Firebolt::Types::BooleanMap expectedValues;

	for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it)
	{
		expectedValues[it.key()] = it.value().get<bool>();
	}
	
	// Getting the actual value
	Firebolt::Discovery::DiscoveryPolicy policy = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().policy(&error);
	
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve policy from Discovery.policy() method";

	// Convert DiscoveryPolicy to BooleanMap for comparison
	Firebolt::Types::BooleanMap actualValues;
	actualValues["enableRecommendations"] = policy.enableRecommendations;
	actualValues["shareWatchHistory"] = policy.shareWatchHistory;
	actualValues["rememberWatchedPrograms"] = policy.rememberWatchedPrograms;

	EXPECT_EQ(actualValues, expectedValues);
}

TEST_F(DiscoveryTest, EntityInfo)
{
    Firebolt::Error error = Firebolt::Error::None;
    nlohmann::json_abi_v3_11_3::json expectedValue = nlohmann::json::parse(jsonEngine->get_value("Discovery.entityInfo"));

    // Mock EntityInfoResult
    Firebolt::Discovery::EntityInfoResult entityInfoResult;
    entityInfoResult.expires = "2025-01-01T00:00:00.000Z";
    entityInfoResult.entity = mockEntityInfo();
    entityInfoResult.related = std::nullopt;

    bool actualValue = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().entityInfo(entityInfoResult, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve status from Discovery.entityInfo() method";
    EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(DiscoveryTest, PurchasedContent)
{
	Firebolt::Error error = Firebolt::Error::None;
	nlohmann::json_abi_v3_11_3::json expectedValue = nlohmann::json::parse(jsonEngine->get_value("Discovery.purchasedContent"));

	// Mock purchasedContentResult
	Firebolt::Discovery::PurchasedContentResult purchasedContentResult;
	purchasedContentResult.expires = "2025-01-01T00:00:00.000Z";
	purchasedContentResult.totalCount = 10;
    purchasedContentResult.entries.push_back(mockEntityInfo());

	bool actualValue = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().purchasedContent(purchasedContentResult, &error);

	EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(DiscoveryTest, WatchNext)
{
	Firebolt::Error error = Firebolt::Error::None;
	nlohmann::json_abi_v3_11_3::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Discovery.watchNext"));
	
	std::string title = "A Fantastic Show";
	Firebolt::Entertainment::ContentIdentifiers contentIdentifiers;
	contentIdentifiers.entityId = "partner.com/entity/456";

	bool result = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().watchNext(title, contentIdentifiers, std::nullopt, std::nullopt, &error);
	
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve policy from Discovery.watchNext() method";
	EXPECT_EQ(result, expectedJson);
}


TEST_F(DiscoveryTest, Entitlements)
{
	Firebolt::Error error = Firebolt::Error::None;
	nlohmann::json_abi_v3_11_3::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Discovery.entitlements"));

	std::vector<Firebolt::Entertainment::Entitlement> mockEntitlements = {
		{"entitlement1", "2023-01-01T00:00:00Z", "2023-12-31T23:59:59Z"},
		{"entitlement2", std::nullopt, "2023-12-31T23:59:59Z"},
		{"entitlement3", "2023-01-01T00:00:00Z", std::nullopt}
	};
	bool success = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().entitlements(mockEntitlements, &error);

	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve policy from Discovery.entitlements() method";
	EXPECT_EQ(success, expectedJson);
}


TEST_F(DiscoveryTest, ContentAccess)
{
	auto expectedValue = jsonEngine->get_value("Discovery.contentAccess");
	
	std::vector<Firebolt::Discovery::Availability> mockAvailabilities = {
		{Firebolt::Discovery::AvailabilityType::CHANNEL_LINEUP, "availability1", "catalog1", "2023-01-01T00:00:00Z", "2023-12-31T23:59:59Z"},
		{Firebolt::Discovery::AvailabilityType::PROGRAM_LINEUP, "availability2", std::nullopt, "2023-01-01T00:00:00Z", std::nullopt}
	};

	std::vector<Firebolt::Entertainment::Entitlement> mockEntitlements = {
		{"entitlement1", "2023-01-01T00:00:00Z", "2023-12-31T23:59:59Z"},
		{"entitlement2", std::nullopt, "2023-12-31T23:59:59Z"},
		{"entitlement3", "2023-01-01T00:00:00Z", std::nullopt}
	};
	
	Firebolt::Discovery::ContentAccessIdentifiers mockContentAccessIdentifiers = {
    	mockAvailabilities,
    	mockEntitlements
	};
	
	Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().contentAccess(mockContentAccessIdentifiers, &error);
	
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call Discovery.contentAccess() method";
}

TEST_F(DiscoveryTest, ClearContentAccess)
{
	auto expectedValue = jsonEngine->get_value("Discovery.clearContentAccess");
	
	Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().clearContentAccess(&error);
	
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call Discovery.clearContentAccess() method";
}

TEST_F(DiscoveryTest, Launch)
{
	nlohmann::json_abi_v3_11_3::json expectedValue = nlohmann::json::parse(jsonEngine->get_value("Discovery.launch"));
	
	std::string appId = "123";
	Firebolt::Intents::LaunchIntent launchIntent;
	launchIntent.action = "launch";
	launchIntent.context.source = "source";

	bool actualValue = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().launch("appId", launchIntent, &error);
	
	EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call Discovery.launch() method";
	EXPECT_EQ(actualValue, expectedValue);
}
