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


TEST_F(DeviceTest, setName) {
    std::string expected_name = "MyDevice";
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().setName(expected_name, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling DeviceInterface.setName() method";
}

TEST_F(DeviceTest, name) {
    std::string expectedValues = jsonEngine->get_value("Device.name");
    std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling DeviceInterface.name() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), name) << "Error: wrong name returned by DeviceInterface.name()";
}

TEST_F(DeviceTest, provision) {
    std::string accountId = "12345";
    std::string deviceId = "67890";
    std::optional<std::string> distributorId = "distributor1";
    
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().provision(accountId, deviceId, distributorId, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling DeviceInterface.provision() method";
}


// Events related tests
struct DeviceNameSettings : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification
{
    void onDeviceNameChanged(const std::string &) override;
};

void DeviceNameSettings::onDeviceNameChanged(const std::string &name)
{
    std::cout << "onDeviceNameChanged event fired";
}

TEST_F(DeviceTest, subscribeOnDeviceNameChanged)
{
    DeviceNameSettings deviceNameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(deviceNameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to DeviceNameSettings";
}

TEST_F(DeviceTest, unsubscribeOnDeviceNameChanged)
{
    DeviceNameSettings deviceNameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(deviceNameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to DeviceNameSettings";
}

struct NameSettings : public Firebolt::Device::IDevice::IOnNameChangedNotification
{
    void onNameChanged(const std::string &) override;
};

void NameSettings::onNameChanged(const std::string &name)
{
    std::cout << "onNameChanged event fired";
}

TEST_F(DeviceTest, subscribeOnNameChanged)
{
    NameSettings nameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(nameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to NameSettings";
}

TEST_F(DeviceTest, unsubscribeOnNameChanged)
{
    NameSettings nameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(nameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to NameSettings";
}
