#include "unit.h"

using namespace Firebolt::PinChallenge;

struct PinChallengeProvider : public IPinChallengeProvider
{
public:
    PinChallengeProvider();
    ~PinChallengeProvider() override = default;
    void challenge(const PinChallenge &parameters, std::unique_ptr<IPinChallengeSession> session) override;
    void SendMessage(bool response);

private:
    void startPinChallengeSession(const PinChallenge &parameters, std::unique_ptr<IPinChallengeSession> session);

private:
    std::unique_ptr<IPinChallengeSession> _session;
    PinChallenge _parameters;
    bool _challengeInput;
};

class PinChallengeTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    PinChallengeProvider _pinChallengeProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

PinChallengeProvider::PinChallengeProvider()
    : _session(nullptr), _parameters(), _challengeInput(false)
{
}

void PinChallengeProvider::SendMessage(bool response)
{
}

void PinChallengeProvider::challenge(const PinChallenge &parameters, std::unique_ptr<IPinChallengeSession> session)
{
    std::cout << "PinChallengeProvider challenge is invoked" << std::endl;
    startPinChallengeSession(parameters, std::move(session));
}

void PinChallengeProvider::startPinChallengeSession(const PinChallenge &parameters, std::unique_ptr<IPinChallengeSession> session)
{
    _session = std::move(session);
    _parameters = parameters;
    _challengeInput = true;
}

TEST_F(PinChallengeTest, registerPinChallengeProvider)
{
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().provide(_pinChallengeProvider);
}