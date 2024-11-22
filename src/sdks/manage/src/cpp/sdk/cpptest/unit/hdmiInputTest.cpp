#include "unit.h"

class HDMIInputTest : public ::testing::Test
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

TEST_F(HDMIInputTest, setAutoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setAutoLowLatencyModeCapable(port, expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.setAutoLowLatencyModeCapable() method";
}

TEST_F(HDMIInputTest, autoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.autoLowLatencyModeCapable");
    bool enabled = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.autoLowLatencyModeCapable() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues) == "true", enabled) << "Error: wrong autoLowLatencyModeCapable returned by HDMIInputInterface.autoLowLatencyModeCapable()";
}

TEST_F(HDMIInputTest, close)
{
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().close(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.close() method";
}

TEST_F(HDMIInputTest, edidVersion)
{
    std::string port = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.edidVersion");
    Firebolt::HDMIInput::EDIDVersion edidVersion = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port, &error);

    std::string actual_version;
    switch (edidVersion)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_version = "1.4";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_version = "2.0";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_version = "unknown";
        break;
    default:
        actual_version = "invalid_version";
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.edidVersion() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_version) << "Error: wrong edidVersion returned by HDMIInputInterface.edidVersion()";
}

TEST_F(HDMIInputTest, setEdidVersion)
{
    std::string port = "HDMI1";
    Firebolt::HDMIInput::EDIDVersion expected_version = Firebolt::HDMIInput::EDIDVersion::V1_4; // Replace with appropriate enum value
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setEdidVersion(port, expected_version, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.setEdidVersion() method";
}

TEST_F(HDMIInputTest, lowLatencyMode)
{
    std::string expectedValues = jsonEngine->get_value("HDMIInput.lowLatencyMode");
    bool enabled = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().lowLatencyMode(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.lowLatencyMode() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues) == "true", enabled) << "Error: wrong lowLatencyMode returned by HDMIInputInterface.lowLatencyMode()";
}

TEST_F(HDMIInputTest, setLowLatencyMode)
{
    bool expected_value = true;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setLowLatencyMode(expected_value, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.setLowLatencyMode() method";
}

TEST_F(HDMIInputTest, open)
{
    std::string portId = "HDMI1";
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().open(portId, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.open() method";
}

TEST_F(HDMIInputTest, port)
{
    std::string portId = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.port");
    Firebolt::HDMIInput::HDMIInputPort port = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().port(portId, &error);

    std::string actual_settings;
    actual_settings += "\"arcCapable\":" + std::string(port.arcCapable ? "true" : "false") + ",";
    actual_settings += "\"arcConnected\":" + std::string(port.arcConnected ? "true" : "false") + ",";
    actual_settings += "\"autoLowLatencyModeCapable\":" + std::string(port.autoLowLatencyModeCapable ? "true" : "false") + ",";
    actual_settings += "\"autoLowLatencyModeSignalled\":" + std::string(port.autoLowLatencyModeSignalled ? "true" : "false") + ",";
    actual_settings += "\"connected\":" + std::string(port.connected ? "true" : "false") + ",";

    switch (port.edidVersion)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_settings += "\"edidVersion\":\"1.4\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_settings += "\"edidVersion\":\"2.0\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_settings += "\"edidVersion\":unknown,";
        break;
    default:
        actual_settings += "\"edidVersion\":invalid,";
    }
    actual_settings += "\"port\":\"" + std::string(port.port) + "\",";

    switch (port.signal)
    {
    case Firebolt::HDMIInput::HDMISignalStatus::NONE:
        actual_settings += "\"signal\":\"none\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::STABLE:
        actual_settings += "\"signal\":\"stable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE:
        actual_settings += "\"signal\":\"unstable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED:
        actual_settings += "\"signal\":\"unsupported\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN:
        actual_settings += "\"signal\":\"unknown\"";
        break;
    default:
        actual_settings += "\"signal\":\"invalid\"";
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.port() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_settings) << "Error: wrong port returned by HDMIInputInterface.port()";
}

TEST_F(HDMIInputTest, ports)
{
    std::string expectedValues = jsonEngine->get_value("HDMIInput.ports");
    std::vector<Firebolt::HDMIInput::HDMIInputPort> ports = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().ports(&error);

    Firebolt::HDMIInput::HDMIInputPort port = ports[0];
    std::string actual_settings = "{";
    actual_settings += "\"arcCapable\":" + std::string(port.arcCapable ? "true" : "false") + ",";
    actual_settings += "\"arcConnected\":" + std::string(port.arcConnected ? "true" : "false") + ",";
    actual_settings += "\"autoLowLatencyModeCapable\":" + std::string(port.autoLowLatencyModeCapable ? "true" : "false") + ",";
    actual_settings += "\"autoLowLatencyModeSignalled\":" + std::string(port.autoLowLatencyModeSignalled ? "true" : "false") + ",";
    actual_settings += "\"connected\":" + std::string(port.connected ? "true" : "false") + ",";

    switch (port.edidVersion)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_settings += "\"edidVersion\":\"1.4\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_settings += "\"edidVersion\":\"2.0\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_settings += "\"edidVersion\":unknown,";
        break;
    default:
        actual_settings += "\"edidVersion\":invalid,";
    }
    actual_settings += "\"port\":\"" + std::string(port.port) + "\",";

    switch (port.signal)
    {
    case Firebolt::HDMIInput::HDMISignalStatus::NONE:
        actual_settings += "\"signal\":\"none\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::STABLE:
        actual_settings += "\"signal\":\"stable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE:
        actual_settings += "\"signal\":\"unstable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED:
        actual_settings += "\"signal\":\"unsupported\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN:
        actual_settings += "\"signal\":\"unknown\"";
        break;
    default:
        actual_settings += "\"signal\":\"invalid\"";
    }
    actual_settings += "}";

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling HDMIInputInterface.ports() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_settings) << "Error: wrong ports returned by HDMIInputInterface.ports()";
}

// Events related tests
struct AutoLowLatencyModeCapableSettings : public Firebolt::HDMIInput::IHDMIInput::IOnAutoLowLatencyModeCapableChangedNotification
{
    void onAutoLowLatencyModeCapableChanged(const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo &) override;
};

void AutoLowLatencyModeCapableSettings::onAutoLowLatencyModeCapableChanged(const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo &info)
{
    std::cout << "onAutoLowLatencyModeCapableChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeCapableChanged)
{
    AutoLowLatencyModeCapableSettings autoLowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(autoLowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AutoLowLatencyModeCapableSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnAutoLowLatencyModeCapableChanged)
{
    AutoLowLatencyModeCapableSettings autoLowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(autoLowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeCapableSettings";
}

struct AutoLowLatencyModeSignalSettings : public Firebolt::HDMIInput::IHDMIInput::IOnAutoLowLatencyModeSignalChangedNotification
{
    void onAutoLowLatencyModeSignalChanged(const Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo &) override;
};

void AutoLowLatencyModeSignalSettings::onAutoLowLatencyModeSignalChanged(const Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo &info)
{
    std::cout << "onAutoLowLatencyModeSignalChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeSignalChanged)
{
    AutoLowLatencyModeSignalSettings autoLowLatencySignalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(autoLowLatencySignalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AutoLowLatencyModeSignalSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnAutoLowLatencyModeSignalChanged)
{
    AutoLowLatencyModeSignalSettings autoLowLatencySignalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(autoLowLatencySignalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeSignalSettings";
}

struct ConnectionSettings : public Firebolt::HDMIInput::IHDMIInput::IOnConnectionChangedNotification
{
    void onConnectionChanged(const Firebolt::HDMIInput::ConnectionChangedInfo &) override;
};

void ConnectionSettings::onConnectionChanged(const Firebolt::HDMIInput::ConnectionChangedInfo &info)
{
    std::cout << "onConnectionChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnConnectionChanged)
{
    ConnectionSettings connectionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(connectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to ConnectionSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnConnectionChanged)
{
    ConnectionSettings connectionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(connectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to ConnectionSettings";
}

struct EdidVersionSettings : public Firebolt::HDMIInput::IHDMIInput::IOnEdidVersionChangedNotification
{
    void onEdidVersionChanged(const Firebolt::HDMIInput::EDIDVersion &) override;
};

void EdidVersionSettings::onEdidVersionChanged(const Firebolt::HDMIInput::EDIDVersion &version)
{
    std::cout << "onEdidVersionChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnEdidVersionChanged)
{
    EdidVersionSettings edidVersionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe("port_name", edidVersionSettings, &error); // Replace "port_name" with actual port name
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EdidVersionSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnEdidVersionChanged)
{
    EdidVersionSettings edidVersionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(edidVersionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EdidVersionSettings";
}

struct LowLatencyModeSettings : public Firebolt::HDMIInput::IHDMIInput::IOnLowLatencyModeChangedNotification
{
    void onLowLatencyModeChanged(const bool) override;
};

void LowLatencyModeSettings::onLowLatencyModeChanged(const bool mode)
{
    std::cout << "onLowLatencyModeChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnLowLatencyModeChanged)
{
    LowLatencyModeSettings lowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(lowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LowLatencyModeSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnLowLatencyModeChanged)
{
    LowLatencyModeSettings lowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(lowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LowLatencyModeSettings";
}

struct SignalSettings : public Firebolt::HDMIInput::IHDMIInput::IOnSignalChangedNotification
{
    void onSignalChanged(const Firebolt::HDMIInput::SignalChangedInfo &) override;
};

void SignalSettings::onSignalChanged(const Firebolt::HDMIInput::SignalChangedInfo &info)
{
    std::cout << "onSignalChanged event fired";
}

TEST_F(HDMIInputTest, subscribeOnSignalChanged)
{
    SignalSettings signalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(signalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SignalSettings";
}

TEST_F(HDMIInputTest, unsubscribeOnSignalChanged)
{
    SignalSettings signalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(signalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SignalSettings";
}
