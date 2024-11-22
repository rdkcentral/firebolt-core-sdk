#include "unit.h"

class KeyboardTest : public ::testing::Test
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

    struct KeyboardAsyncResponse : public Firebolt::Keyboard::IKeyboardAsyncResponse {
        void response(const std::string& result, Firebolt::Error *err) override {
            // Handle the response here
            std::cout << "Response received: " << result << std::endl;
        }
    };
};

TEST_F(KeyboardTest, Email)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Keyboard.email"));

    Firebolt::Keyboard::EmailUsage type = Firebolt::Keyboard::EmailUsage::SIGN_IN;
    std::string message = "abc@123.com";
    KeyboardAsyncResponse responseHandler;
    
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestEmail(type, message, responseHandler, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call keyboard.email() method";
}

TEST_F(KeyboardTest, Password)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Keyboard.password"));

    std::string message = "abc123";
    KeyboardAsyncResponse responseHandler;
    
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestPassword(message, responseHandler, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call keyboard.password() method";
}

TEST_F(KeyboardTest, Standard)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Keyboard.standard"));

    std::string message = "hello world";
    KeyboardAsyncResponse responseHandler;
    
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestStandard(message, responseHandler, &error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to call keyboard.standard() method";
}