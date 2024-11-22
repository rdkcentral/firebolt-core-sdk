#include "unit.h"
#include <cmath>

class LocalizationTest : public ::testing::Test
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
};

TEST_F(LocalizationTest, Locality)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.locality"));

    std::string locality = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locality(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve locality from Localization.locality() method";
    EXPECT_EQ(locality, expectedValues);
}

TEST_F(LocalizationTest, PostalCode)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.postalCode"));

    std::string postalCode = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().postalCode(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve postal_code from Localization.postalCode() method";
    EXPECT_EQ(postalCode, expectedValues);
}

TEST_F(LocalizationTest, CountryCode)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.countryCode"));

    std::string countryCode = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve country_code from Localization.countryCode() method";
    EXPECT_EQ(countryCode, expectedValues);
}

TEST_F(LocalizationTest, Language)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.language"));

    std::string language = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().language(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve language from Localization.language() method";
    EXPECT_EQ(language, expectedValues);
}

TEST_F(LocalizationTest, Locale)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.locale"));

    std::string locale = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locale(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve locale from Localization.language() method";
    EXPECT_EQ(locale, expectedValues);
}

TEST_F(LocalizationTest, PreferredAudioLanguages)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.preferredAudioLanguages"));

    std::vector<std::string> preferredAudioLanguages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve preferred_audio_languages from Localization.preferredAudioLanguages() method";
    EXPECT_EQ(preferredAudioLanguages, expectedValues);
}

TEST_F(LocalizationTest, AdditionalInfo)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Localization.additionalInfo"));

    Firebolt::Localization::Info additionalInfo = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve additional_info from Localization.additionalInfo() method";
    EXPECT_EQ(additionalInfo, expectedValues);
}

// Helper function to round a double to 4 decimal places
double roundTo4Decimals(double value) {
    return std::round(value * 10000.0) / 10000.0;
}

TEST_F(LocalizationTest, LatLon)
{
    nlohmann::json expectedJson;
    try
    {
        std::string jsonString = jsonEngine->get_value("Localization.latlon");
        expectedJson = nlohmann::json::parse(jsonString);
    }
    catch (const nlohmann::json::exception &e)
    {
        FAIL() << "Failed to parse JSON: " << e.what();
    }

    // Validate that expectedJson is an array and has the required number of elements
    if (!expectedJson.is_array())
    {
        FAIL() << "Expected JSON is not an array: " << expectedJson.dump(4);
    }

    if (expectedJson.size() != 2)
    {
        FAIL() << "Expected JSON array does not have 2 elements: " << expectedJson.dump(4);
    }

    // Getting the actual value from the LocalizationInterface
    Firebolt::Localization::LatLon latlon = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().latlon(&error);

    // Round the actual values to 4 decimal places
    double roundedLat = roundTo4Decimals(latlon.first);
    double roundedLon = roundTo4Decimals(latlon.second);

    // Convert actual value to JSON
    nlohmann::json actualJson = {roundedLat, roundedLon};

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve latlon from Localization.latlon() method";
    EXPECT_EQ(actualJson, expectedJson);
}
