#include "unit.h"

using namespace Firebolt::Keyboard;

struct KeyboardProvider : public IKeyboardProvider
{
public:
    KeyboardProvider();
    ~KeyboardProvider() override = default;
    void standard(const KeyboardParameters &parameters, std::unique_ptr<IKeyboardSession> session) override;
    void password(const KeyboardParameters &parameters, std::unique_ptr<IKeyboardSession> session) override;
    void email(const KeyboardParameters &parameters, std::unique_ptr<IKeyboardSession> session) override;
    void SendMessage(bool response);

private:
    void startKeyboardSession(const KeyboardParameters &parameters, std::unique_ptr<IKeyboardSession> session);

private:
    std::unique_ptr<IKeyboardSession> _session;
    KeyboardParameters _parameters;
    bool _keyInput;
};

class KeyboardTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    KeyboardProvider _keyboardProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

KeyboardProvider::KeyboardProvider()
    : _session(nullptr), _parameters(), _keyInput(false)
{
}

void KeyboardProvider::standard(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    std::cout << "KeyboardProvider Standard is invoked" << std::endl;
    startKeyboardSession(parameters, std::move(session));
}

void KeyboardProvider::password(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    std::cout << "KeyboardProvider Password is invoked" << std::endl;
    startKeyboardSession(parameters, std::move(session));
}

void KeyboardProvider::email(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    std::cout << "KeyboardProvider Email is invoked" << std::endl;
    startKeyboardSession(parameters, std::move(session));
}

void KeyboardProvider::SendMessage(bool response)
{
}

void KeyboardProvider::startKeyboardSession(const KeyboardParameters &parameters, std::unique_ptr<IKeyboardSession> session)
{
    _session = std::move(session);
    _parameters = parameters;
    _keyInput = true;
}

TEST_F(KeyboardTest, registerKeyboardProvider)
{
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().provide(_keyboardProvider);
}

