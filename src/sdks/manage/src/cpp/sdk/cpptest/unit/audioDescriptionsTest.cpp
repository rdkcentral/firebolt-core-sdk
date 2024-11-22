#include "unit.h"

class AudioDescriptionsTest : public ::testing::Test
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

TEST_F(AudioDescriptionsTest, enabled)
{
    auto expectedValues = jsonEngine->get_value("AudioDescriptions.enabled");
    bool enable = Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().enabled(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AudioDescriptions.enabled() method";
    EXPECT_EQ(expectedValues == "true", enable) << "Error: AudioDescriptions.enabled() dose not returns enabled";
}

TEST_F(AudioDescriptionsTest, setEnabled)
{
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().setEnabled(true, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling AudioDescriptions.setEnabled() method";
}

struct EnabledChanged : public Firebolt::AudioDescriptions::IAudioDescriptions::IOnEnabledChangedNotification
{
    void onEnabledChanged(const bool) override;
};

void EnabledChanged::onEnabledChanged(const bool)
{
    std::cout << "onAudioDescriptionEnabledChanged event fired";
}

TEST_F(AudioDescriptionsTest, subscribeonEnabledChanged)
{
    EnabledChanged enabledChanged;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().subscribe(enabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledChanged";
}

TEST_F(AudioDescriptionsTest, unsubscribeonEnabledChanged)
{
    EnabledChanged enabledChanged;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().unsubscribe(enabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledChanged";
}