#include "unit.h"

class AdvertisingTest : public ::testing::Test
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

TEST_F(AdvertisingTest, resetIdentifier)
{
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().resetIdentifier(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AdvertisingInterface.resetIdentifier() method";
}

TEST_F(AdvertisingTest, skipRestriction)
{
    std::string expectedValues = jsonEngine->get_value("Advertising.skipRestriction");
    Firebolt::Advertising::SkipRestriction restriction = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().skipRestriction(&error);

    std::string actual_skip_restriction;
    switch (restriction)
    {
    case Firebolt::Advertising::SkipRestriction::NONE:
        actual_skip_restriction = "none";
        break;
    case Firebolt::Advertising::SkipRestriction::ADS_UNWATCHED:
        actual_skip_restriction = "ads_unwatched";
        break;
    case Firebolt::Advertising::SkipRestriction::ADS_ALL:
        actual_skip_restriction = "ads_all";
        break;
    case Firebolt::Advertising::SkipRestriction::ALL:
        actual_skip_restriction = "all";
        break;
    default:
        actual_skip_restriction = "unknown";
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AdvertisingInterface.skipRestriction() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_skip_restriction) << "Error: wrong skipRestriction returned by AdvertisingInterface.skipRestriction()";
}

TEST_F(AdvertisingTest, setSkipRestriction)
{
    Firebolt::Advertising::SkipRestriction expected_value = Firebolt::Advertising::SkipRestriction::ADS_ALL; // Replace with the appropriate enum value
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().setSkipRestriction(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AdvertisingInterface.setSkipRestriction() method";
}

// Events Tests
struct SkipRestrictionChanged : public Firebolt::Advertising::IAdvertising::IOnSkipRestrictionChangedNotification
{
    void onSkipRestrictionChanged(const Firebolt::Advertising::SkipRestriction &) override;
};

Firebolt::Advertising::SkipRestriction newSkipRestriction;
void SkipRestrictionChanged::onSkipRestrictionChanged(const Firebolt::Advertising::SkipRestriction &skipRestriction)
{
    std::cout << "onSkipRestrictionChanged event fired";
}

TEST_F(AdvertisingTest, subscribeOnSkipRestrictionChanged)
{
    SkipRestrictionChanged skipRestrictionChanged;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().subscribe(skipRestrictionChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SkipRestrictionChanged";
}

TEST_F(AdvertisingTest, unsubscribeOnSkipRestrictionChanged)
{
    SkipRestrictionChanged skipRestrictionChanged;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().unsubscribe(skipRestrictionChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SkipRestrictionChanged";
}