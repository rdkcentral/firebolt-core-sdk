#include "unit.h"

class DeviceTest : public ::testing::Test
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

TEST_F(DeviceTest, Id)
{

    auto actual_value = jsonEngine->get_value("Device.id");

    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve id from Device.id() method";
    EXPECT_EQ(id, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Distributor)
{

    auto actual_value = jsonEngine->get_value("Device.distributor");

    auto distributor = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve distributor from Device.distributor() method";
    EXPECT_EQ(distributor, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Platform)
{

    auto actual_value = jsonEngine->get_value("Device.platform");

    auto platform = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve platform from Device.platform() method";
    EXPECT_EQ(platform, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Uid)
{

    auto actual_value = jsonEngine->get_value("Device.uid");

    auto uid = Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve uid from Device.uid() method";
    EXPECT_EQ(uid, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Type)
{

    auto actual_value = jsonEngine->get_value("Device.type");

    auto type = Firebolt::IFireboltAccessor::Instance().DeviceInterface().type(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve type from Device.type() method";
    EXPECT_EQ(type, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Model)
{

    auto actual_value = jsonEngine->get_value("Device.model");

    auto model = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve model from Device.model() method";
    EXPECT_EQ(model, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Sku)
{

    auto actual_value = jsonEngine->get_value("Device.sku");

    auto sku = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve sku from Device.sku() method";
    EXPECT_EQ(sku, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, TestDeviceMake)
{

    auto actual_value = jsonEngine->get_value("Device.make");

    auto make = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve make from Device.make() method";
    EXPECT_EQ(make, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Hdcp)
{

    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdcp"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it)
    {
        expectedValues[it.key()] = it.value().get<bool>();
    }

    // Getting the actual value from the DeviceInterface
    Firebolt::Types::BooleanMap hdcp = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve hdcp from Device.hdcp() method";
    EXPECT_EQ(hdcp, expectedValues);
}

TEST_F(DeviceTest, Hdr)
{

    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdr"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it)
    {
        expectedValues[it.key()] = it.value().get<bool>();
    }

    // Getting the actual value from the DeviceInterface
    Firebolt::Types::BooleanMap hdr = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve hdr from Device.hdr() method";
    EXPECT_EQ(hdr, expectedValues);
}

std::string AudioProfileToString(Firebolt::Types::AudioProfile profile)
{
    switch (profile)
    {
    case Firebolt::Types::AudioProfile::STEREO:
        return "stereo";
    case Firebolt::Types::AudioProfile::DOLBY_DIGITAL_5_1:
        return "dolbyDigital5.1+";
    case Firebolt::Types::AudioProfile::DOLBY_ATMOS:
        return "dolbyAtmos";
    default:
        return "dolbyDigital5.1";
    }
}

TEST_F(DeviceTest, Audio)
{

    // Parse expected JSON values
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.audio"));

    // Getting the actual value from the DeviceInterface
    const Firebolt::Device::AudioProfiles audio = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve audio from Device.audio() method";

    // Convert actualValue (AudioProfiles map) to JSON
    nlohmann::json actualJson;
    for (const auto &item : audio)
    {
        std::string profileKey = AudioProfileToString(item.first); // Replace this with the correct conversion function
        actualJson[profileKey] = item.second;
    }

    EXPECT_EQ(actualJson, expectedJson);
}

TEST_F(DeviceTest, Network)
{

    // Hardcoded expected values
    Firebolt::Device::NetworkInfo expectedValues;
    expectedValues.state = Firebolt::Device::NetworkState::CONNECTED;
    expectedValues.type = Firebolt::Device::NetworkType::WIFI;

    // Getting the actual value from the DeviceInterface
    Firebolt::Device::NetworkInfo network = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network(&error);

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve network from Device.network() method";
    EXPECT_EQ(network.state, expectedValues.state);
    EXPECT_EQ(network.type, expectedValues.type);
}

TEST_F(DeviceTest, ScreenResolution)
{

    // Parse expected JSON values
    nlohmann::json expectedJson;
    try
    {
        std::string jsonString = jsonEngine->get_value("Device.screenResolution");
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

    // Getting the actual value from the DeviceInterface
    Firebolt::Device::Resolution screenResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution(&error);

    // Convert actual value to JSON
    nlohmann::json actualJson = {screenResolution.first, screenResolution.second};

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve actualResolution from Device.screenResolution() method";
    EXPECT_EQ(actualJson, expectedJson);
}

TEST_F(DeviceTest, VideoResolution)
{

    // Parse expected JSON values
    nlohmann::json expectedJson;
    try
    {
        std::string jsonString = jsonEngine->get_value("Device.videoResolution");
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

    // Getting the actual value from the DeviceInterface
    Firebolt::Device::Resolution videoResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().videoResolution(&error);

    // Convert actual value to JSON
    nlohmann::json actualJson = {videoResolution.first, videoResolution.second};

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve videoResolution from Device.videoResolution() method";
    EXPECT_EQ(actualJson, expectedJson);
}

TEST_F(DeviceTest, Name)
{

    auto actual_value = jsonEngine->get_value("Device.name");

    auto name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve name from Device.name() method";
    EXPECT_EQ(name, REMOVE_QUOTES(actual_value));
}
