#include "unit.h"

class DiscoveryTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct SignInSettings : public Firebolt::Discovery::IDiscovery::IOnSignInNotification
{
    void onSignIn(const Firebolt::Discovery::Event &) override;
};

void SignInSettings::onSignIn(const Firebolt::Discovery::Event &event)
{
    std::cout << "onSignIn event fired";
}

TEST_F(DiscoveryTest, subscribeOnSignIn)
{
    SignInSettings signInSettings;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(signInSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SignInSettings";
}

TEST_F(DiscoveryTest, unsubscribeOnSignIn)
{
    SignInSettings signInSettings;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(signInSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SignInSettings";
}

struct SignOutSettings : public Firebolt::Discovery::IDiscovery::IOnSignOutNotification
{
    void onSignOut(const Firebolt::Discovery::Event &) override;
};

void SignOutSettings::onSignOut(const Firebolt::Discovery::Event &event)
{
    std::cout << "onSignOut event fired";
}

TEST_F(DiscoveryTest, subscribeOnSignOut)
{
    SignOutSettings signOutSettings;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(signOutSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SignOutSettings";
}

TEST_F(DiscoveryTest, unsubscribeOnSignOut)
{
    SignOutSettings signOutSettings;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(signOutSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SignOutSettings";
}
