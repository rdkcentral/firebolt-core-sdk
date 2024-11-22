#include "unit.h"

using namespace Firebolt::AcknowledgeChallenge;

struct AcknowledgeChallengeProvider : public IAcknowledgeChallengeProvider
{
    AcknowledgeChallengeProvider();
    ~AcknowledgeChallengeProvider() override = default;
    void SendMessage(bool response);
    void challenge(const Challenge &parameters, std::unique_ptr<IAcknowledgeChallengeSession> session) override;

private:
    void startAcknowledgeChallengeSession(const Challenge &parameters, std::unique_ptr<IAcknowledgeChallengeSession> session);

private:
    std::unique_ptr<IAcknowledgeChallengeSession> _session;
    Challenge _parameters;
    bool _challengeInput;
};

class AcknowledgeChallengeTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    AcknowledgeChallengeProvider _acknowledgeChallengeProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

AcknowledgeChallengeProvider::AcknowledgeChallengeProvider()
    : _session(nullptr), _parameters(), _challengeInput(false)
{
}

void AcknowledgeChallengeProvider::SendMessage(bool response)
{
}

void AcknowledgeChallengeProvider::startAcknowledgeChallengeSession(const Firebolt::AcknowledgeChallenge::Challenge &parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session)
{
    _session = std::move(session);
    _parameters = parameters;
    _challengeInput = true;
}

void AcknowledgeChallengeProvider::challenge(const Challenge &parameters, std::unique_ptr<IAcknowledgeChallengeSession> session)
{
    std::cout << "AcknowledgeChallengeProvider challenge is invoked" << std::endl;
    startAcknowledgeChallengeSession(parameters, std::move(session));
}

TEST_F(AcknowledgeChallengeTest, registerAcknowledgeChallengeProvider)
{
    Firebolt::IFireboltAccessor::Instance().AcknowledgeChallengeInterface().provide(_acknowledgeChallengeProvider);
}
