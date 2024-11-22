#include "unit.h"

class PrivacyTest : public ::testing::Test
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

TEST_F(PrivacyTest, setAllowACRCollection)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowACRCollection(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowACRCollection() method";
}

TEST_F(PrivacyTest, allowACRCollection)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowACRCollection");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowACRCollection(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowACRCollection() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowACRCollection returned by PrivacyInterface.allowACRCollection()";
}

TEST_F(PrivacyTest, setAllowAppContentAdTargeting)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowAppContentAdTargeting(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowAppContentAdTargeting() method";
}

TEST_F(PrivacyTest, allowAppContentAdTargeting)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowAppContentAdTargeting");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowAppContentAdTargeting(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowAppContentAdTargeting() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowAppContentAdTargeting returned by PrivacyInterface.allowAppContentAdTargeting()";
}

TEST_F(PrivacyTest, setAllowCameraAnalytics)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowCameraAnalytics(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowCameraAnalytics() method";
}

TEST_F(PrivacyTest, allowCameraAnalytics)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowCameraAnalytics");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowCameraAnalytics(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowCameraAnalytics() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowCameraAnalytics returned by PrivacyInterface.allowCameraAnalytics()";
}

TEST_F(PrivacyTest, setAllowPersonalization)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowPersonalization(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowPersonalization() method";
}

TEST_F(PrivacyTest, allowPersonalization)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowPersonalization");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowPersonalization(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowPersonalization() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowPersonalization returned by PrivacyInterface.allowPersonalization()";
}

TEST_F(PrivacyTest, setAllowPrimaryBrowseAdTargeting)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowPrimaryBrowseAdTargeting(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowPrimaryBrowseAdTargeting() method";
}

TEST_F(PrivacyTest, allowPrimaryBrowseAdTargeting)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowPrimaryBrowseAdTargeting");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowPrimaryBrowseAdTargeting(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowPrimaryBrowseAdTargeting() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowPrimaryBrowseAdTargeting returned by PrivacyInterface.allowPrimaryBrowseAdTargeting()";
}

TEST_F(PrivacyTest, setAllowPrimaryContentAdTargeting)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowPrimaryContentAdTargeting(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowPrimaryContentAdTargeting() method";
}

TEST_F(PrivacyTest, allowPrimaryContentAdTargeting)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowPrimaryContentAdTargeting");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowPrimaryContentAdTargeting(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowPrimaryContentAdTargeting() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowPrimaryContentAdTargeting returned by PrivacyInterface.allowPrimaryContentAdTargeting()";
}

TEST_F(PrivacyTest, setAllowProductAnalytics)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowProductAnalytics(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowProductAnalytics() method";
}

TEST_F(PrivacyTest, allowProductAnalytics)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowProductAnalytics");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowProductAnalytics(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowProductAnalytics() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowProductAnalytics returned by PrivacyInterface.allowProductAnalytics()";
}

TEST_F(PrivacyTest, setAllowRemoteDiagnostics)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowRemoteDiagnostics(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowRemoteDiagnostics() method";
}

TEST_F(PrivacyTest, allowResumePoints)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowResumePoints");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowResumePoints(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowResumePoints() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowResumePoints returned by PrivacyInterface.allowResumePoints()";
}

TEST_F(PrivacyTest, setAllowResumePoints)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowResumePoints(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowResumePoints() method";
}

TEST_F(PrivacyTest, allowUnentitledPersonalization)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowUnentitledPersonalization");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowUnentitledPersonalization(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowUnentitledPersonalization() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowUnentitledPersonalization returned by PrivacyInterface.allowUnentitledPersonalization()";
}

TEST_F(PrivacyTest, setAllowUnentitledPersonalization)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowUnentitledPersonalization(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowUnentitledPersonalization() method";
}

TEST_F(PrivacyTest, allowUnentitledResumePoints)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowUnentitledResumePoints");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowUnentitledResumePoints(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowUnentitledResumePoints() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowUnentitledResumePoints returned by PrivacyInterface.allowUnentitledResumePoints()";
}

TEST_F(PrivacyTest, setAllowUnentitledResumePoints)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowUnentitledResumePoints(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowUnentitledResumePoints() method";
}

TEST_F(PrivacyTest, allowWatchHistory)
{
    std::string expectedValues = jsonEngine->get_value("Privacy.allowWatchHistory");
    bool allow = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowWatchHistory(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.allowWatchHistory() method";
    EXPECT_EQ(expectedValues == "true", allow) << "Error: wrong allowWatchHistory returned by PrivacyInterface.allowWatchHistory()";
}

TEST_F(PrivacyTest, setAllowWatchHistory)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowWatchHistory(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.setAllowWatchHistory() method";
}

TEST_F(PrivacyTest, settings)
{

    std::string expectedValues = jsonEngine->get_value("Privacy.settings");

    Firebolt::Privacy::PrivacySettings settings = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().settings(&error);

    std::string actual_settings = "{";
    actual_settings += "\"allowACRCollection\":" + std::string(settings.allowACRCollection ? "true" : "false") + ",";
    actual_settings += "\"allowAppContentAdTargeting\":" + std::string(settings.allowAppContentAdTargeting ? "true" : "false") + ",";
    actual_settings += "\"allowCameraAnalytics\":" + std::string(settings.allowCameraAnalytics ? "true" : "false") + ",";
    actual_settings += "\"allowPersonalization\":" + std::string(settings.allowPersonalization ? "true" : "false") + ",";
    actual_settings += "\"allowPrimaryBrowseAdTargeting\":" + std::string(settings.allowPrimaryBrowseAdTargeting ? "true" : "false") + ",";
    actual_settings += "\"allowPrimaryContentAdTargeting\":" + std::string(settings.allowPrimaryContentAdTargeting ? "true" : "false") + ",";
    actual_settings += "\"allowProductAnalytics\":" + std::string(settings.allowProductAnalytics ? "true" : "false") + ",";
    actual_settings += "\"allowRemoteDiagnostics\":" + std::string(settings.allowRemoteDiagnostics ? "true" : "false") + ",";
    actual_settings += "\"allowResumePoints\":" + std::string(settings.allowResumePoints ? "true" : "false") + ",";
    actual_settings += "\"allowUnentitledPersonalization\":" + std::string(settings.allowUnentitledPersonalization ? "true" : "false") + ",";
    actual_settings += "\"allowUnentitledResumePoints\":" + std::string(settings.allowUnentitledResumePoints ? "true" : "false") + ",";
    actual_settings += "\"allowWatchHistory\":" + std::string(settings.allowWatchHistory ? "true" : "false");
    actual_settings += "}";
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling PrivacyInterface.settings() method";
    EXPECT_EQ(expectedValues, actual_settings) << "Error: wrong settings returned by PrivacyInterface.settings()";
}

// Events Tests
struct AllowACRCollectionSettings : public Firebolt::Privacy::IPrivacy::IOnAllowACRCollectionChangedNotification
{
    void onAllowACRCollectionChanged(const bool) override;
};

void AllowACRCollectionSettings::onAllowACRCollectionChanged(const bool isAllowed)
{
    std::cout << "onAllowACRCollectionChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowACRCollectionChanged)
{
    AllowACRCollectionSettings allowACRCollectionSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowACRCollectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowACRCollectionSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowACRCollectionChanged)
{
    AllowACRCollectionSettings allowACRCollectionSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowACRCollectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowACRCollectionSettings";
}

struct AllowAppContentAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowAppContentAdTargetingChangedNotification
{
    void onAllowAppContentAdTargetingChanged(const bool) override;
};

void AllowAppContentAdTargetingSettings::onAllowAppContentAdTargetingChanged(const bool isAllowed)
{
    std::cout << "onAllowAppContentAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowAppContentAdTargetingChanged)
{
    AllowAppContentAdTargetingSettings allowAppContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowAppContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowAppContentAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowAppContentAdTargetingChanged)
{
    AllowAppContentAdTargetingSettings allowAppContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowAppContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowAppContentAdTargetingSettings";
}

struct AllowCameraAnalyticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowCameraAnalyticsChangedNotification
{
    void onAllowCameraAnalyticsChanged(const bool) override;
};

void AllowCameraAnalyticsSettings::onAllowCameraAnalyticsChanged(const bool isAllowed)
{
    std::cout << "onAllowCameraAnalyticsChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowCameraAnalyticsChanged)
{
    AllowCameraAnalyticsSettings allowCameraAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowCameraAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowCameraAnalyticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowCameraAnalyticsChanged)
{
    AllowCameraAnalyticsSettings allowCameraAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowCameraAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowCameraAnalyticsSettings";
}

struct AllowPersonalizationSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPersonalizationChangedNotification
{
    void onAllowPersonalizationChanged(const bool) override;
};

void AllowPersonalizationSettings::onAllowPersonalizationChanged(const bool isAllowed)
{
    std::cout << "onAllowPersonalizationChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPersonalizationChanged)
{
    AllowPersonalizationSettings allowPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPersonalizationSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPersonalizationChanged)
{
    AllowPersonalizationSettings allowPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPersonalizationSettings";
}

struct AllowPrimaryBrowseAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPrimaryBrowseAdTargetingChangedNotification
{
    void onAllowPrimaryBrowseAdTargetingChanged(const bool) override;
};

void AllowPrimaryBrowseAdTargetingSettings::onAllowPrimaryBrowseAdTargetingChanged(const bool isAllowed)
{
    std::cout << "onAllowPrimaryBrowseAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPrimaryBrowseAdTargetingChanged)
{
    AllowPrimaryBrowseAdTargetingSettings allowPrimaryBrowseAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPrimaryBrowseAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPrimaryBrowseAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPrimaryBrowseAdTargetingChanged)
{
    AllowPrimaryBrowseAdTargetingSettings allowPrimaryBrowseAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPrimaryBrowseAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPrimaryBrowseAdTargetingSettings";
}

struct AllowPrimaryContentAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPrimaryContentAdTargetingChangedNotification
{
    void onAllowPrimaryContentAdTargetingChanged(const bool) override;
};

void AllowPrimaryContentAdTargetingSettings::onAllowPrimaryContentAdTargetingChanged(const bool isAllowed)
{
    std::cout << "onAllowPrimaryContentAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPrimaryContentAdTargetingChanged)
{
    AllowPrimaryContentAdTargetingSettings allowPrimaryContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPrimaryContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPrimaryContentAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPrimaryContentAdTargetingChanged)
{
    AllowPrimaryContentAdTargetingSettings allowPrimaryContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPrimaryContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPrimaryContentAdTargetingSettings";
}

struct AllowProductAnalyticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowProductAnalyticsChangedNotification
{
    void onAllowProductAnalyticsChanged(const bool) override;
};

void AllowProductAnalyticsSettings::onAllowProductAnalyticsChanged(const bool isAllowed)
{
    std::cout << "onAllowProductAnalyticsChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowProductAnalyticsChanged)
{
    AllowProductAnalyticsSettings allowProductAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowProductAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowProductAnalyticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowProductAnalyticsChanged)
{
    AllowProductAnalyticsSettings allowProductAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowProductAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowProductAnalyticsSettings";
}

struct AllowRemoteDiagnosticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowRemoteDiagnosticsChangedNotification
{
    void onAllowRemoteDiagnosticsChanged(const bool) override;
};

void AllowRemoteDiagnosticsSettings::onAllowRemoteDiagnosticsChanged(const bool isAllowed)
{
    std::cout << "onAllowRemoteDiagnosticsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowRemoteDiagnosticsChanged)
{
    AllowRemoteDiagnosticsSettings allowRemoteDiagnosticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowRemoteDiagnosticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowRemoteDiagnosticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowRemoteDiagnosticsChanged)
{
    AllowRemoteDiagnosticsSettings allowRemoteDiagnosticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowRemoteDiagnosticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowRemoteDiagnosticsSettings";
}

struct AllowResumePointsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowResumePointsChangedNotification
{
    void onAllowResumePointsChanged(const bool) override;
};

void AllowResumePointsSettings::onAllowResumePointsChanged(const bool isAllowed)
{
    std::cout << "onAllowResumePointsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowResumePointsChanged)
{
    AllowResumePointsSettings allowResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowResumePointsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowResumePointsChanged)
{
    AllowResumePointsSettings allowResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowResumePointsSettings";
}

struct AllowUnentitledPersonalizationSettings : public Firebolt::Privacy::IPrivacy::IOnAllowUnentitledPersonalizationChangedNotification
{
    void onAllowUnentitledPersonalizationChanged(const bool) override;
};

void AllowUnentitledPersonalizationSettings::onAllowUnentitledPersonalizationChanged(const bool isAllowed)
{
    std::cout << "onAllowUnentitledPersonalizationChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowUnentitledPersonalizationChanged)
{
    AllowUnentitledPersonalizationSettings allowUnentitledPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowUnentitledPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowUnentitledPersonalizationSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowUnentitledPersonalizationChanged)
{
    AllowUnentitledPersonalizationSettings allowUnentitledPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowUnentitledPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowUnentitledPersonalizationSettings";
}

struct AllowUnentitledResumePointsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowUnentitledResumePointsChangedNotification
{
    void onAllowUnentitledResumePointsChanged(const bool) override;
};

void AllowUnentitledResumePointsSettings::onAllowUnentitledResumePointsChanged(const bool isAllowed)
{
    std::cout << "onAllowUnentitledResumePointsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowUnentitledResumePointsChanged)
{
    AllowUnentitledResumePointsSettings allowUnentitledResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowUnentitledResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowUnentitledResumePointsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowUnentitledResumePointsChanged)
{
    AllowUnentitledResumePointsSettings allowUnentitledResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowUnentitledResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowUnentitledResumePointsSettings";
}

struct AllowWatchHistorySettings : public Firebolt::Privacy::IPrivacy::IOnAllowWatchHistoryChangedNotification
{
    void onAllowWatchHistoryChanged(const bool) override;
};

void AllowWatchHistorySettings::onAllowWatchHistoryChanged(const bool isAllowed)
{
    std::cout << "onAllowWatchHistoryChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowWatchHistoryChanged)
{
    AllowWatchHistorySettings allowWatchHistorySettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowWatchHistorySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowWatchHistorySettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowWatchHistoryChanged)
{
    AllowWatchHistorySettings allowWatchHistorySettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowWatchHistorySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowWatchHistorySettings";
}
