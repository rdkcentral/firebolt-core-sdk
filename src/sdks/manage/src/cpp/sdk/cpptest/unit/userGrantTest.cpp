#include "unit.h"

using namespace Firebolt::UserGrants;
using namespace Firebolt::Capabilities;

class UserGrantsTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:example-capability:sub-capability";
    Role role;
    std::optional<GrantModificationOptions> options = std::nullopt;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

std::string grantInfoLifespanToString(GrantInfoLifespan lifespan)
{
    switch (lifespan)
    {
    case GrantInfoLifespan::ONCE:
        return "once";
    case GrantInfoLifespan::FOREVER:
        return "forever";
    case GrantInfoLifespan::APP_ACTIVE:
        return "appActive";
    case GrantInfoLifespan::POWER_ACTIVE:
        return "powerActive";
    case GrantInfoLifespan::SECONDS:
        return "seconds";
    default:
        return "unknown";
    }
}

std::string roleToString(Role role)
{
    switch (role)
    {
    case Role::USE:
        return "use";
    case Role::MANAGE:
        return "manage";
    case Role::PROVIDE:
        return "provide";
    default:
        return "unknown";
    }
}

std::string grantStateToString(GrantState state)
{
    switch (state)
    {
    case GrantState::GRANTED:
        return "granted";
    case GrantState::DENIED:
        return "denied";
    default:
        return "unknown";
    }
}

std::string stringifyGrantInfo(const std::vector<GrantInfo> &grants)
{
    std::string result = "[";
    for (const auto &grant : grants)
    {
        result += "{";
        if (grant.app.has_value())
        {
            result += "\"app\":{\"id\":\"" + grant.app.value().id + "\",";
            if (grant.app.value().title.has_value())
            {
                result += "\"title\":\"" + grant.app.value().title.value() + "\"";
            }
            result += "},";
        }
        result += "\"capability\":\"" + std::string(grant.capability) + "\",";
        if (grant.expires.has_value())
        {
            result += "\"expires\":\"" + grant.expires.value() + "\",";
        }
        result += "\"lifespan\":\"" + grantInfoLifespanToString(grant.lifespan) + "\",";
        result += "\"role\":\"" + roleToString(grant.role) + "\",";
        result += "\"state\":\"" + grantStateToString(grant.state) + "\"";
        result += "},";
    }
    if (!grants.empty())
    {
        result.pop_back(); // Remove the last comma
    }
    result += "]";
    return result;
}

TEST_F(UserGrantsTest, app)
{
    std::string expectedValues = jsonEngine->get_value("UserGrants.app");
    std::string appId = "appId";
    std::vector<GrantInfo> info = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().app(appId, &error);

    std::string info_string = stringifyGrantInfo(info);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.app() method";
    EXPECT_EQ(expectedValues, info_string) << "Error: wrong info returned by UserGrantsInterface.app()";
}

TEST_F(UserGrantsTest, capability)
{
    std::string expectedValues = jsonEngine->get_value("UserGrants.capability");
    std::vector<GrantInfo> info = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().capability(capability, &error);

    std::string info_string = stringifyGrantInfo(info);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.capability() method";
    EXPECT_EQ(expectedValues, info_string) << "Error: wrong info returned by UserGrantsInterface.capability()";
}

TEST_F(UserGrantsTest, clear)
{
    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().clear(role, capability, options, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.clear() method";
}

TEST_F(UserGrantsTest, deny)
{
    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().deny(role, capability, options, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.deny() method";
}

TEST_F(UserGrantsTest, device)
{
    std::string expectedValues = jsonEngine->get_value("UserGrants.device");
    std::vector<GrantInfo> info = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().device(&error);

    std::string info_string = stringifyGrantInfo(info);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.device() method";
    EXPECT_EQ(expectedValues, info_string) << "Error: wrong info returned by UserGrantsInterface.device()";
}

TEST_F(UserGrantsTest, grant)
{
    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().grant(role, capability, options, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.grant() method";
}

TEST_F(UserGrantsTest, request)
{
    std::string expectedValues = jsonEngine->get_value("UserGrants.request");

    std::string appId = "appId";
    std::vector<Permission> permissions = {
        {std::make_optional<Role>(Role::USE), "xrn:firebolt:capability:example-capability:sub-capability"},
        {std::nullopt, "xrn:firebolt:capability:example-capability:sub-capability"},
        {std::make_optional<Role>(Role::MANAGE), "xrn:firebolt:capability:example-capability:sub-capability"}};
    std::optional<RequestOptions> req_options = std::nullopt;

    std::vector<GrantInfo> info = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().request(appId, permissions, req_options, &error);

    std::string info_string = stringifyGrantInfo(info);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling UserGrantsInterface.request() method";
    EXPECT_EQ(expectedValues, info_string) << "Error: wrong info returned by UserGrantsInterface.request()";
}
