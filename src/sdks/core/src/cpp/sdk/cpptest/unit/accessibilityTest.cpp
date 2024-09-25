#include "unit.h"

class AccessibilityTest : public ::testing::Test
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

    std::string fontFamilyToString(Firebolt::Accessibility::FontFamily fontFamily)
    {
        std::string str = "";
        switch (fontFamily)
        {
        case Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF:
            str = "monospaced_serif";
            break;
        case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF:
            str = "proportional_serif";
            break;
        case Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF:
            str = "monospaced_sanserif";
            break;
        case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF:
            str = "proportional_sanserif";
            break;
        case Firebolt::Accessibility::FontFamily::SMALLCAPS:
            str = "smallcaps";
            break;
        case Firebolt::Accessibility::FontFamily::CURSIVE:
            str = "cursive";
            break;
        case Firebolt::Accessibility::FontFamily::CASUAL:
            str = "casual";
            break;
        default:
            str = "unknown";
        }
        return str;
    }

    std::string fontEdgeToString(Firebolt::Accessibility::FontEdge fontEdge)
    {
        std::string str = "";
        switch (fontEdge)
        {
        case Firebolt::Accessibility::FontEdge::NONE:
            str = "none";
            break;
        case Firebolt::Accessibility::FontEdge::RAISED:
            str = "raised";
            break;
        case Firebolt::Accessibility::FontEdge::DEPRESSED:
            str = "depressed";
            break;
        case Firebolt::Accessibility::FontEdge::UNIFORM:
            str = "uniform";
            break;
        case Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT:
            str = "drop_shadow_left";
            break;
        case Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT:
            str = "drop_shadow_right";
            break;
        default:
            str = "unknown";
        }
        return str;
    }
};

TEST_F(AccessibilityTest, ClosedCaptions)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.closedCaptions"));

    auto closedCaptions = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptions(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve closedCaptions from Accessibility.closedCaptions() method";
    EXPECT_EQ(closedCaptions.enabled, expectedValues["enabled"]);

    EXPECT_EQ(closedCaptions.styles.backgroundColor.value(), expectedValues["styles"]["backgroundColor"]);
    EXPECT_EQ(closedCaptions.styles.backgroundOpacity.value(), expectedValues["styles"]["backgroundOpacity"]);
    EXPECT_EQ(closedCaptions.styles.fontColor.value(), expectedValues["styles"]["fontColor"]);

    if (closedCaptions.styles.fontEdge.has_value())
        EXPECT_EQ(fontEdgeToString(closedCaptions.styles.fontEdge.value()), expectedValues["styles"]["fontEdge"]);

    EXPECT_EQ(closedCaptions.styles.fontEdgeColor.value(), expectedValues["styles"]["fontEdgeColor"]);

    if (closedCaptions.styles.fontFamily.has_value())
        EXPECT_EQ(fontFamilyToString(closedCaptions.styles.fontFamily.value()), expectedValues["styles"]["fontFamily"]);

    EXPECT_EQ(closedCaptions.styles.fontOpacity.value(), expectedValues["styles"]["fontOpacity"]);
    EXPECT_EQ(closedCaptions.styles.fontSize.value(), expectedValues["styles"]["fontSize"]);
    EXPECT_EQ(closedCaptions.styles.textAlign.value(), expectedValues["styles"]["textAlign"]);
    EXPECT_EQ(closedCaptions.styles.textAlignVertical.value(), expectedValues["styles"]["textAlignVertical"]);
    EXPECT_EQ(closedCaptions.styles.windowColor.value(), expectedValues["styles"]["windowColor"]);
    EXPECT_EQ(closedCaptions.styles.windowOpacity.value(), expectedValues["styles"]["windowOpacity"]);

    EXPECT_EQ(closedCaptions.preferredLanguages.value()[0], expectedValues["preferredLanguages"][0]);
    EXPECT_EQ(closedCaptions.preferredLanguages.value()[1], expectedValues["preferredLanguages"][1]);
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.closedCaptionsSettings"));

    auto closedCaptionSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve closedCaptionSettings from Accessibility.closedCaptionSettings() method";
    EXPECT_EQ(closedCaptionSettings.enabled, expectedValues["enabled"]);

    EXPECT_EQ(closedCaptionSettings.styles.backgroundColor.value(), expectedValues["styles"]["backgroundColor"]);
    EXPECT_EQ(closedCaptionSettings.styles.backgroundOpacity.value(), expectedValues["styles"]["backgroundOpacity"]);
    EXPECT_EQ(closedCaptionSettings.styles.fontColor.value(), expectedValues["styles"]["fontColor"]);

    if (closedCaptionSettings.styles.fontEdge.has_value())
        EXPECT_EQ(fontEdgeToString(closedCaptionSettings.styles.fontEdge.value()), expectedValues["styles"]["fontEdge"]);

    EXPECT_EQ(closedCaptionSettings.styles.fontEdgeColor.value(), expectedValues["styles"]["fontEdgeColor"]);

    if (closedCaptionSettings.styles.fontFamily.has_value())
        EXPECT_EQ(fontFamilyToString(closedCaptionSettings.styles.fontFamily.value()), expectedValues["styles"]["fontFamily"]);

    EXPECT_EQ(closedCaptionSettings.styles.fontOpacity.value(), expectedValues["styles"]["fontOpacity"]);
    EXPECT_EQ(closedCaptionSettings.styles.fontSize.value(), expectedValues["styles"]["fontSize"]);
    EXPECT_EQ(closedCaptionSettings.styles.textAlign.value(), expectedValues["styles"]["textAlign"]);
    EXPECT_EQ(closedCaptionSettings.styles.textAlignVertical.value(), expectedValues["styles"]["textAlignVertical"]);
    EXPECT_EQ(closedCaptionSettings.styles.windowColor.value(), expectedValues["styles"]["windowColor"]);
    EXPECT_EQ(closedCaptionSettings.styles.windowOpacity.value(), expectedValues["styles"]["windowOpacity"]);

    EXPECT_EQ(closedCaptionSettings.preferredLanguages.value()[0], expectedValues["preferredLanguages"][0]);
    EXPECT_EQ(closedCaptionSettings.preferredLanguages.value()[1], expectedValues["preferredLanguages"][1]);
}

TEST_F(AccessibilityTest, VoiceGuidance)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.voiceGuidance"));

    auto voiceGuidance = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidance(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve voiceGuidance from Accessibility.voiceGuidance() method";

    EXPECT_EQ(voiceGuidance.enabled, expectedValues["enabled"]);
    EXPECT_EQ(voiceGuidance.speed, expectedValues["speed"]);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.voiceGuidanceSettings"));

    auto voiceGuidanceSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidanceSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve voiceGuidanceSettings from Accessibility.voiceGuidanceSettings() method";

    EXPECT_EQ(voiceGuidanceSettings.enabled, expectedValues["enabled"]);
    EXPECT_EQ(voiceGuidanceSettings.speed, expectedValues["speed"]);
}

TEST_F(AccessibilityTest, AudioDescriptionSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.audioDescriptionSettings"));

    auto audioDescriptionSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().audioDescriptionSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve audioDescriptionSettings from Accessibility.audioDescriptionSettings() method";

    EXPECT_EQ(audioDescriptionSettings.enabled, expectedValues["enabled"]);
}
