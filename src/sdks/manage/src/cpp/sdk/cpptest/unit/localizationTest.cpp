#include "unit.h"

class LocalizationTest : public ::testing::Test
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

TEST_F(LocalizationTest, addAdditionalInfo)
{
    std::string key = "sampleKey";
    float value = 1.23f;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().addAdditionalInfo(key, value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.addAdditionalInfo() method";
}

TEST_F(LocalizationTest, additionalInfo)
{
    std::string expectedValues = jsonEngine->get_value("Localization.additionalInfo");
    Firebolt::Localization::Info info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);

    std::string actual_info;
    for (const auto &item : info)
    {
        actual_info += item.first + "=" + std::to_string(item.second) + ",";
    }
    actual_info = actual_info.substr(0, actual_info.size() - 1);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.additionalInfo() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_info) << "Error: wrong additionalInfo returned by LocalizationInterface.additionalInfo()";
}

TEST_F(LocalizationTest, setCountryCode)
{
    std::string expected_value = "US";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setCountryCode(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setCountryCode() method";
}

TEST_F(LocalizationTest, countryCode)
{
    std::string expectedValues = jsonEngine->get_value("Localization.countryCode");
    std::string code = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.countryCode() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), code) << "Error: wrong countryCode returned by LocalizationInterface.countryCode()";
}

TEST_F(LocalizationTest, setLanguage)
{
    std::string expected_value = "en";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setLanguage(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setLanguage() method";
}

TEST_F(LocalizationTest, language)
{
    std::string expectedValues = jsonEngine->get_value("Localization.language");
    std::string lang = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().language(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.language() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), lang) << "Error: wrong language returned by LocalizationInterface.language()";
}

TEST_F(LocalizationTest, setLocale)
{
    std::string expected_value = "en-US";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setLocale(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setLocale() method";
}

TEST_F(LocalizationTest, locale)
{
    std::string expectedValues = jsonEngine->get_value("Localization.locale");
    std::string locale = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locale(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.locale() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), locale) << "Error: wrong locale returned by LocalizationInterface.locale()";
}

TEST_F(LocalizationTest, setLocality)
{
    std::string expected_value = "Rockville";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setLocality(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setLocality() method";
}

TEST_F(LocalizationTest, locality)
{
    std::string expectedValues = jsonEngine->get_value("Localization.locality");
    std::string locality = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locality(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.locality() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), locality) << "Error: wrong locality returned by LocalizationInterface.locality()";
}

TEST_F(LocalizationTest, setPostalCode)
{
    std::string expected_value = "20850";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setPostalCode(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setPostalCode() method";
}

TEST_F(LocalizationTest, postalCode)
{
    std::string expectedValues = jsonEngine->get_value("Localization.postalCode");
    std::string postalCode = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().postalCode(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.postalCode() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), postalCode) << "Error: wrong postalCode returned by LocalizationInterface.postalCode()";
}

TEST_F(LocalizationTest, setPreferredAudioLanguages)
{
    std::vector<std::string> expected_languages = {"eng", "spa"};
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setPreferredAudioLanguages(expected_languages, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setPreferredAudioLanguages() method";
}

TEST_F(LocalizationTest, preferredAudioLanguages)
{
    std::string expectedValues = jsonEngine->get_value("Localization.preferredAudioLanguages");
    std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);

    std::string actual_languages = "[";
    for (const auto &lang : languages)
    {
        actual_languages += "\"" + lang + "\",";
    }
    actual_languages = actual_languages.substr(0, actual_languages.size() - 1); // Remove trailing comma
    actual_languages += "]";

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.preferredAudioLanguages() method";
    EXPECT_EQ(expectedValues, actual_languages) << "Error: wrong preferredAudioLanguages returned by LocalizationInterface.preferredAudioLanguages()";
}

TEST_F(LocalizationTest, removeAdditionalInfo)
{
    std::string key = "sampleKey";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().removeAdditionalInfo(key, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.removeAdditionalInfo() method";
}

TEST_F(LocalizationTest, setTimeZone)
{
    std::string expected_value = "America/Los_Angeles";
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setTimeZone(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.setTimeZone() method";
}

TEST_F(LocalizationTest, timeZone)
{
    std::string expectedValues = jsonEngine->get_value("Localization.timeZone");
    std::string timeZone = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().timeZone(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling LocalizationInterface.timeZone() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), timeZone) << "Error: wrong timeZone returned by LocalizationInterface.timeZone()";
}

// Events tests
struct CountryCodeSettings : public Firebolt::Localization::ILocalization::IOnCountryCodeChangedNotification
{
    void onCountryCodeChanged(const std::string &) override;
};

void CountryCodeSettings::onCountryCodeChanged(const std::string &code)
{
    std::cout << "onCountryCodeChanged event fired";
}

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged)
{
    CountryCodeSettings countryCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(countryCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to CountryCodeSettings";
}

TEST_F(LocalizationTest, unsubscribeOnCountryCodeChanged)
{
    CountryCodeSettings countryCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(countryCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to CountryCodeSettings";
}

struct LanguageSettings : public Firebolt::Localization::ILocalization::IOnLanguageChangedNotification
{
    void onLanguageChanged(const std::string &) override;
};

void LanguageSettings::onLanguageChanged(const std::string &language)
{
    std::cout << "onLanguageChanged event fired with language: " << language;
}

TEST_F(LocalizationTest, subscribeOnLanguageChanged)
{
    LanguageSettings languageSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(languageSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LanguageSettings";
}

TEST_F(LocalizationTest, unsubscribeOnLanguageChanged)
{
    LanguageSettings languageSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(languageSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LanguageSettings";
}

struct LocaleSettings : public Firebolt::Localization::ILocalization::IOnLocaleChangedNotification
{
    void onLocaleChanged(const std::string &) override;
};

void LocaleSettings::onLocaleChanged(const std::string &locale)
{
    std::cout << "onLocaleChanged event fired with locale: " << locale;
}

TEST_F(LocalizationTest, subscribeOnLocaleChanged)
{
    LocaleSettings localeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(localeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LocaleSettings";
}

TEST_F(LocalizationTest, unsubscribeOnLocaleChanged)
{
    LocaleSettings localeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(localeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LocaleSettings";
}

struct LocalitySettings : public Firebolt::Localization::ILocalization::IOnLocalityChangedNotification
{
    void onLocalityChanged(const std::string &) override;
};

void LocalitySettings::onLocalityChanged(const std::string &locality)
{
    std::cout << "onLocalityChanged event fired with locality: " << locality;
}

TEST_F(LocalizationTest, subscribeOnLocalityChanged)
{
    LocalitySettings localitySettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(localitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LocalitySettings";
}

TEST_F(LocalizationTest, unsubscribeOnLocalityChanged)
{
    LocalitySettings localitySettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(localitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LocalitySettings";
}

struct PostalCodeSettings : public Firebolt::Localization::ILocalization::IOnPostalCodeChangedNotification
{
    void onPostalCodeChanged(const std::string &) override;
};

void PostalCodeSettings::onPostalCodeChanged(const std::string &postalCode)
{
    std::cout << "onPostalCodeChanged event fired with postal code: " << postalCode;
}

TEST_F(LocalizationTest, subscribeOnPostalCodeChanged)
{
    PostalCodeSettings postalCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(postalCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PostalCodeSettings";
}

TEST_F(LocalizationTest, unsubscribeOnPostalCodeChanged)
{
    PostalCodeSettings postalCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(postalCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PostalCodeSettings";
}

struct PreferredAudioLanguagesSettings : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification
{
    void onPreferredAudioLanguagesChanged(const std::vector<std::string> &) override;
};

void PreferredAudioLanguagesSettings::onPreferredAudioLanguagesChanged(const std::vector<std::string> &languages)
{
    std::cout << "onPreferredAudioLanguagesChanged event fired with languages: ";
    for (const auto &lang : languages)
    {
        std::cout << lang << " ";
    }
    std::cout << std::endl;
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged)
{
    PreferredAudioLanguagesSettings preferredAudioLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(preferredAudioLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PreferredAudioLanguagesSettings";
}

TEST_F(LocalizationTest, unsubscribeOnPreferredAudioLanguagesChanged)
{
    PreferredAudioLanguagesSettings preferredAudioLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(preferredAudioLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PreferredAudioLanguagesSettings";
}

struct TimeZoneSettings : public Firebolt::Localization::ILocalization::IOnTimeZoneChangedNotification
{
    void onTimeZoneChanged(const std::string &) override;
};

void TimeZoneSettings::onTimeZoneChanged(const std::string &timeZone)
{
    std::cout << "onTimeZoneChanged event fired with time zone: " << timeZone;
}

TEST_F(LocalizationTest, subscribeOnTimeZoneChanged)
{
    TimeZoneSettings timeZoneSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(timeZoneSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TimeZoneSettings";
}

TEST_F(LocalizationTest, unsubscribeOnTimeZoneChanged)
{
    TimeZoneSettings timeZoneSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(timeZoneSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TimeZoneSettings";
}
