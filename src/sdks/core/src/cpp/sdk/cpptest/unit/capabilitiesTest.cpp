#include "unit.h"

class CapabilitiesTest : public ::testing::Test
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

TEST_F(CapabilitiesTest, Supported)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.supported"));

    std::string capability = "xrn:firebolt:capability:wifi:scan";

    bool supported = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().supported(capability, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve supported from Capabilities.supported() method";
    EXPECT_EQ(supported, expectedValues);
}

TEST_F(CapabilitiesTest, Available)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.available"));

    std::string capability = "xrn:firebolt:capability:token:device";

    bool available = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().available(capability, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve available from Capabilities.available() method";
    EXPECT_EQ(available, expectedValues);
}

TEST_F(CapabilitiesTest, Permitted)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.permitted"));

    std::string capability = "xrn:firebolt:capability:input:keyboard";

    // Initialize options with a role
    std::optional<Firebolt::Capabilities::CapabilityOption> options;
    options.emplace(); // Initialize the optional
    options->role = Firebolt::Capabilities::Role::MANAGE;

    // Call the permitted function
    bool permitted = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().permitted(capability, options, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve permitted from Capabilities.permitted() method";
    EXPECT_EQ(permitted, expectedValues);
}

TEST_F(CapabilitiesTest, Granted)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.granted"));
    std::string capability = "xrn:firebolt:capability:localization:postal-code";

    std::optional<Firebolt::Capabilities::CapabilityOption> options;
    bool granted = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().granted(capability, options, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve granted from Capabilities.granted() method";
    EXPECT_EQ(granted, expectedValues);
}

TEST_F(CapabilitiesTest, Info)
{
    // Parse the expected values from the JSON
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.info"));

    // Extract the expected result for the specific capability
    nlohmann::json expectedValue;
    for (const auto &item : expectedValues)
    {
        if (item["capability"] == "xrn:firebolt:capability:device:model")
        {
            expectedValue = item;
            break;
        }
    }
    // Define the capabilities to query
    std::vector<std::string> capabilities = {
        "xrn:firebolt:capability:device:model"};

    std::vector<Firebolt::Capabilities::CapabilityInfo> info = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().info(capabilities, &error);

    // Ensure there's at least one result
    ASSERT_FALSE(info.empty());

    // Compare the first actual value with the expected value
    Firebolt::Capabilities::CapabilityInfo actualValue = info[0];

    // Compare each field
    EXPECT_EQ(actualValue.capability, expectedValue["capability"].get<std::string>());
    EXPECT_EQ(actualValue.supported, expectedValue["supported"].get<bool>());
    EXPECT_EQ(actualValue.available, expectedValue["available"].get<bool>());

    if (expectedValue.contains("use"))
    {
        if (expectedValue["use"].contains("permitted"))
        {
            auto expectedPermitted = expectedValue["use"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["use"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.use.permitted, expectedPermitted);
        }
        if (expectedValue["use"].contains("granted"))
        {
            auto expectedGranted = expectedValue["use"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["use"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.use.granted, expectedGranted);
        }
    }

    if (expectedValue.contains("manage"))
    {
        if (expectedValue["manage"].contains("permitted"))
        {
            auto expectedPermitted = expectedValue["manage"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["manage"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.manage.permitted, expectedPermitted);
        }
        if (expectedValue["manage"].contains("granted"))
        {
            auto expectedGranted = expectedValue["manage"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["manage"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.manage.granted, expectedGranted);
        }
    }

    if (expectedValue.contains("provide"))
    {
        if (expectedValue["provide"].contains("permitted"))
        {
            auto expectedPermitted = expectedValue["provide"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["provide"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.provide.permitted, expectedPermitted);
        }
        if (expectedValue["provide"].contains("granted"))
        {
            auto expectedGranted = expectedValue["provide"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["provide"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.provide.granted, expectedGranted);
        }
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve info from Capabilities.info() method";
}
