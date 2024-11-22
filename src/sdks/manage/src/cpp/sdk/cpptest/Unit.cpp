#include "gtest/gtest.h"
#include "ManageSDKTest.h"

int main(int argc, char **argv)
{
    std::string url = "ws://localhost:9998";
    ManageSDKTest::CreateFireboltInstance(url);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}