#include "unit.h"

class VoiceGuidanceTest : public ::testing::Test
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

TEST_F(VoiceGuidanceTest, setEnabled)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().setEnabled(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling VoiceGuidanceInterface.setEnabled() method";
}

TEST_F(VoiceGuidanceTest, enabled)
{
    std::string expectedValues = jsonEngine->get_value("VoiceGuidance.enabled");
    bool enabled = Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().enabled(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling VoiceGuidanceInterface.enabled() method";
    EXPECT_EQ(expectedValues == "true", enabled) << "Error: wrong enabled value returned by VoiceGuidanceInterface.enabled()";
}

TEST_F(VoiceGuidanceTest, setSpeed)
{
    float expected_value = 1.5f;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().setSpeed(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling VoiceGuidanceInterface.setSpeed() method";
}

TEST_F(VoiceGuidanceTest, speed)
{
    std::string expectedValues = jsonEngine->get_value("VoiceGuidance.speed");
    float speed = Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().speed(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling VoiceGuidanceInterface.speed() method";
    EXPECT_EQ(stof(expectedValues), speed) << "Error: wrong speed value returned by VoiceGuidanceInterface.speed()";
}

// Events Tests
struct EnabledSettings : public Firebolt::VoiceGuidance::IVoiceGuidance::IOnEnabledChangedNotification
{
    void onEnabledChanged(const bool) override;
};

void EnabledSettings::onEnabledChanged(const bool isEnabled)
{
    std::cout << "onEnabledChanged event fired with isEnabled: " << isEnabled;
}

TEST_F(VoiceGuidanceTest, subscribeOnEnabledChanged)
{
    EnabledSettings enabledSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().subscribe(enabledSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledSettings";
}

TEST_F(VoiceGuidanceTest, unsubscribeOnEnabledChanged)
{
    EnabledSettings enabledSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().unsubscribe(enabledSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledSettings";
}

struct SpeedSettings : public Firebolt::VoiceGuidance::IVoiceGuidance::IOnSpeedChangedNotification
{
    void onSpeedChanged(const float) override;
};

void SpeedSettings::onSpeedChanged(const float speed)
{
    std::cout << "onSpeedChanged event fired with speed: " << speed;
}

TEST_F(VoiceGuidanceTest, subscribeOnSpeedChanged)
{
    SpeedSettings speedSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().subscribe(speedSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SpeedSettings";
}

TEST_F(VoiceGuidanceTest, unsubscribeOnSpeedChanged)
{
    SpeedSettings speedSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().unsubscribe(speedSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SpeedSettings";
}
