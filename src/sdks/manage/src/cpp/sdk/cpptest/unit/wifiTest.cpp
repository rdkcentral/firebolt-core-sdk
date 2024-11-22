#include "unit.h"

using namespace Firebolt::Wifi;

class WifiTest : public ::testing::Test
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

std::string wifiSecurityModeToString(WifiSecurityMode mode)
{
    switch (mode)
    {
    case WifiSecurityMode::NONE:
        return "none";
    case WifiSecurityMode::WEP_64:
        return "wep64";
    case WifiSecurityMode::WEP_128:
        return "wep128";
    case WifiSecurityMode::WPA_PSK_TKIP:
        return "wpaPskTkip";
    case WifiSecurityMode::WPA_PSK_AES:
        return "wpaPskAes";
    case WifiSecurityMode::WPA_2PSK_TKIP:
        return "wpa2PskTkip";
    case WifiSecurityMode::WPA_2PSK_AES:
        return "wpa2PskAes";
    case WifiSecurityMode::WPA_ENTERPRISE_TKIP:
        return "wpaEnterpriseTkip";
    case WifiSecurityMode::WPA_ENTERPRISE_AES:
        return "wpaEnterpriseAes";
    case WifiSecurityMode::WPA_2ENTERPRISE_TKIP:
        return "wpa2EnterpriseTkip";
    case WifiSecurityMode::WPA_2ENTERPRISE_AES:
        return "wpa2EnterpriseAes";
    case WifiSecurityMode::WPA_2PSK:
        return "wpa2Psk";
    case WifiSecurityMode::WPA_2ENTERPRISE:
        return "wpa2Enterprise";
    case WifiSecurityMode::WPA_3PSK_AES:
        return "wpa3PskAes";
    case WifiSecurityMode::WPA_3SAE:
        return "wpa3Sae";
    default:
        return "unknown";
    }
}

std::string removeParentheses(const std::string &str)
{
    std::string result;
    for (char ch : str)
    {
        if (ch != '(' && ch != ')')
        {
            result += ch;
        }
    }
    return result;
}

TEST_F(WifiTest, connect)
{
    json expectedValues = json::parse(jsonEngine->get_value("Wifi.connect"));

    std::optional<std::string> ssid = "SSID";
    std::optional<std::string> passphrase = "Passphrase";
    std::optional<WifiSecurityMode> security = WifiSecurityMode::WPA_2PSK;

    AccessPoint connectedWifi = Firebolt::IFireboltAccessor::Instance().WifiInterface().connect(ssid, passphrase, security, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling WifiInterface.connect() method";
    EXPECT_EQ(connectedWifi.ssid, expectedValues["ssid"]) << "SSID mismatch";
    if (connectedWifi.securityMode.has_value())
    {
        EXPECT_EQ(wifiSecurityModeToString(connectedWifi.securityMode.value()), expectedValues["security"]) << "Security mode mismatch";
    }
    EXPECT_EQ(connectedWifi.signalStrength, expectedValues["signalStrength"]) << "signalStrength mismatch";
    if (connectedWifi.frequency.has_value())
    {
        EXPECT_EQ(connectedWifi.frequency, expectedValues["frequency"].get<float>()) << "frequency mismatch";
    }
}

TEST_F(WifiTest, disconnect)
{
    Firebolt::IFireboltAccessor::Instance().WifiInterface().disconnect(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling WifiInterface.disconnect() method";
}

TEST_F(WifiTest, scan)
{
    std::string expectedValues = jsonEngine->get_value("Wifi.scan");

    std::optional<int32_t> timeout = 30;

    AccessPointList apl = Firebolt::IFireboltAccessor::Instance().WifiInterface().scan(timeout, &error);

    std::string apl_string = "{\"list\":[";
    if (apl.list.has_value())
    {
        for (const auto &ap : apl.list.value())
        {
            apl_string += "{";

            if (ap.frequency.has_value())
            {
                std::string s = std::to_string(ap.frequency.value());
                auto pos = s.find('.');

                apl_string += "\"frequency\":" + s.substr(0, pos + 2) + ",";
            }
            if (ap.securityMode.has_value())
            {
                apl_string += "\"security\":\"" + wifiSecurityModeToString(ap.securityMode.value()) + "\",";
            }
            if (ap.signalStrength.has_value())
            {
                apl_string += "\"signalStrength\":" + std::to_string(ap.signalStrength.value()) + ",";
            }
            if (ap.ssid.has_value())
            {
                apl_string += "\"ssid\":\"" + ap.ssid.value() + "\",";
            }

            apl_string.pop_back(); // Remove the last comma
            apl_string += "},";
        }
        apl_string.pop_back(); // Remove the last comma
    }
    apl_string += "]}";

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling WifiInterface.scan() method";
    EXPECT_EQ(expectedValues, apl_string) << "Scan should return at least one access point";
}

TEST_F(WifiTest, wps)
{
    json expectedValues = json::parse(jsonEngine->get_value("Wifi.wps"));
    std::optional<WPSSecurityPin> security = WPSSecurityPin::PIN;

    AccessPoint connectedWifi = Firebolt::IFireboltAccessor::Instance().WifiInterface().wps(security, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling WifiInterface.connect() method";
    EXPECT_EQ(connectedWifi.ssid, expectedValues["ssid"]) << "SSID mismatch";
    if (connectedWifi.securityMode.has_value())
    {
        EXPECT_EQ(wifiSecurityModeToString(connectedWifi.securityMode.value()), expectedValues["security"]) << "Security mode mismatch";
    }
    EXPECT_EQ(connectedWifi.signalStrength, expectedValues["signalStrength"]) << "signalStrength mismatch";
    if (connectedWifi.frequency.has_value())
    {
        EXPECT_EQ(connectedWifi.frequency, expectedValues["frequency"].get<float>()) << "frequency mismatch";
    }
}
