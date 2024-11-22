#include "unit.h"

class ClosedCaptionsTest : public ::testing::Test
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

TEST_F(ClosedCaptionsTest, backgroundColor)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.backgroundColor");
    std::string color = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundColor(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.backgroundColor() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), color) << "Error: wrong color returned by ClosedCaptionsInterface.backgroundColor()";
}

TEST_F(ClosedCaptionsTest, setBackgroundColor)
{
    std::string expected_background_color = "#00002";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundColor(expected_background_color, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setBackgroundColor() method";
}

TEST_F(ClosedCaptionsTest, backgroundOpacity)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.backgroundOpacity");
    float opacity = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundOpacity(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.backgroundOpacity() method";
    EXPECT_EQ(stof(expectedValues), opacity) << "Error: wrong backgroundOpacity returned by ClosedCaptionsInterface.backgroundOpacity()";
}

TEST_F(ClosedCaptionsTest, setBackgroundOpacity)
{
    float expected_background_opacity = 70;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundOpacity(expected_background_opacity, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setBackgroundOpacity() method";
}

TEST_F(ClosedCaptionsTest, setEnabled)
{
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setEnabled(true, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setEnabled() method";
}

TEST_F(ClosedCaptionsTest, setFontColor)
{
    std::string expected_font_color = "#FFFFFF";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontColor(expected_font_color, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontColor() method";
}

TEST_F(ClosedCaptionsTest, fontColor)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontColor");
    std::string color = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontColor(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontColor() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), color) << "Error: wrong fontColor returned by ClosedCaptionsInterface.fontColor()";
}

TEST_F(ClosedCaptionsTest, setFontEdge)
{
    Firebolt::Accessibility::FontEdge expected_edge = Firebolt::Accessibility::FontEdge::UNIFORM;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontEdge(expected_edge, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontEdge() method";
}

TEST_F(ClosedCaptionsTest, fontEdge)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontEdge");
    Firebolt::Accessibility::FontEdge edge = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontEdge(&error);

    std::string actual_font_edge = "unknown";
    switch (edge)
    {
    case Firebolt::Accessibility::FontEdge::NONE:
        actual_font_edge = "none";
        break;
    case Firebolt::Accessibility::FontEdge::RAISED:
        actual_font_edge = "raised";
        break;
    case Firebolt::Accessibility::FontEdge::DEPRESSED:
        actual_font_edge = "depressed";
        break;
    case Firebolt::Accessibility::FontEdge::UNIFORM:
        actual_font_edge = "uniform";
        break;
    case Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT:
        actual_font_edge = "drop_shadow_left";
        break;
    case Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT:
        actual_font_edge = "drop_shadow_right";
        break;
    default:
        actual_font_edge = "unknown";
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontEdge() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_font_edge) << "Error: wrong fontEdge returned by ClosedCaptionsInterface.fontEdge()";
}

TEST_F(ClosedCaptionsTest, setFontEdgeColor)
{
    std::string expected_color = "#FF5733";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontEdgeColor(expected_color, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontEdgeColor() method";
}

TEST_F(ClosedCaptionsTest, fontEdgeColor)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontEdgeColor");
    std::string color = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontEdgeColor(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontEdgeColor() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), color) << "Error: wrong fontEdgeColor returned by ClosedCaptionsInterface.fontEdgeColor()";
}

TEST_F(ClosedCaptionsTest, setFontFamily)
{
    Firebolt::Accessibility::FontFamily expected_family = Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontFamily(expected_family, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontFamily() method";
}

TEST_F(ClosedCaptionsTest, fontFamily)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontFamily");
    Firebolt::Accessibility::FontFamily family = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontFamily(&error);
    std::string actual_family = "unknown";
    switch (family)
    {
    case Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF:
        actual_family = "monospaced_serif";
        break;
    case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF:
        actual_family = "proportional_serif";
        break;
    case Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF:
        actual_family = "monospaced_sanserif";
        break;
    case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF:
        actual_family = "proportional_sanserif";
        break;
    case Firebolt::Accessibility::FontFamily::SMALLCAPS:
        actual_family = "smallcaps";
        break;
    case Firebolt::Accessibility::FontFamily::CURSIVE:
        actual_family = "cursive";
        break;
    case Firebolt::Accessibility::FontFamily::CASUAL:
        actual_family = "casual";
        break;
    default:
        actual_family = "unknown";
    }

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontFamily() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_family) << "Error: wrong fontFamily returned by ClosedCaptionsInterface.fontFamily()";
}

TEST_F(ClosedCaptionsTest, setFontOpacity)
{
    float expected_opacity = 0.75f;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontOpacity(expected_opacity, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontOpacity() method";
}

TEST_F(ClosedCaptionsTest, fontOpacity)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontOpacity");
    float opacity = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontOpacity(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontOpacity() method";
    EXPECT_EQ(stof(expectedValues), opacity) << "Error: wrong fontOpacity returned by ClosedCaptionsInterface.fontOpacity()";
}

TEST_F(ClosedCaptionsTest, setFontSize)
{
    float expected_size = 12.5f;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontSize(expected_size, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setFontSize() method";
}

TEST_F(ClosedCaptionsTest, fontSize)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.fontSize");
    float size = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontSize(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.fontSize() method";
    EXPECT_EQ(stof(expectedValues), size) << "Error: wrong fontSize returned by ClosedCaptionsInterface.fontSize()";
}

TEST_F(ClosedCaptionsTest, setPreferredLanguages)
{
    std::vector<std::string> expected_languages = {"spa", "eng"};
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setPreferredLanguages(expected_languages, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setPreferredLanguages() method";
}

TEST_F(ClosedCaptionsTest, preferredLanguages)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.preferredLanguages");
    std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().preferredLanguages(&error);

    // Convert vector to a string for comparison
    std::string actual_languages;
    for (const auto &lang : languages)
    {
        actual_languages += "\"" + lang + "\",";
    }
    actual_languages = actual_languages.substr(0, actual_languages.size() - 1); // Remove trailing comma

    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.preferredLanguages() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_languages) << "Error: wrong preferredLanguages returned by ClosedCaptionsInterface.preferredLanguages()";
}

TEST_F(ClosedCaptionsTest, setTextAlign)
{
    std::string expected_alignment = "center";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setTextAlign(expected_alignment, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setTextAlign() method";
}

TEST_F(ClosedCaptionsTest, textAlign)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.textAlign");
    std::string alignment = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().textAlign(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.textAlign() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), alignment) << "Error: wrong textAlign returned by ClosedCaptionsInterface.textAlign()";
}

TEST_F(ClosedCaptionsTest, setTextAlignVertical)
{
    std::string expected_alignment = "middle";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setTextAlignVertical(expected_alignment, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setTextAlignVertical() method";
}

TEST_F(ClosedCaptionsTest, textAlignVertical)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.textAlignVertical");
    std::string alignment = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().textAlignVertical(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.textAlignVertical() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), alignment) << "Error: wrong textAlignVertical returned by ClosedCaptionsInterface.textAlignVertical()";
}

TEST_F(ClosedCaptionsTest, setWindowColor)
{
    std::string expected_color = "#000000";
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setWindowColor(expected_color, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setWindowColor() method";
}

TEST_F(ClosedCaptionsTest, windowColor)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.windowColor");
    std::string color = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().windowColor(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.windowColor() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), color) << "Error: wrong windowColor returned by ClosedCaptionsInterface.windowColor()";
}

TEST_F(ClosedCaptionsTest, setWindowOpacity)
{
    float expected_opacity = 0.85f;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setWindowOpacity(expected_opacity, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.setWindowOpacity() method";
}

TEST_F(ClosedCaptionsTest, windowOpacity)
{
    std::string expectedValues = jsonEngine->get_value("ClosedCaptions.windowOpacity");
    float opacity = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().windowOpacity(&error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error on calling ClosedCaptionsInterface.windowOpacity() method";
    EXPECT_EQ(stof(expectedValues), opacity) << "Error: wrong windowOpacity returned by ClosedCaptionsInterface.windowOpacity()";
}

// Events related tests
struct BackgroundColorChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundColorChangedNotification
{
    void onBackgroundColorChanged(const std::string &) override;
};

void BackgroundColorChanged::onBackgroundColorChanged(const std::string &)
{
    std::cout << "onBackgroundColorChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnBackgroundColorChanged)
{
    BackgroundColorChanged backgroundColorChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(backgroundColorChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to BackgroundColorChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnBackgroundColorChanged)
{
    BackgroundColorChanged backgroundColorChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(backgroundColorChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to BackgroundColorChanged";
}

struct BackgroundOpacityChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification
{
    void onBackgroundOpacityChanged(const float) override;
};

void BackgroundOpacityChanged::onBackgroundOpacityChanged(const float)
{
    std::cout << "onBackgroundOpacityChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnBackgroundOpacityChanged)
{
    BackgroundOpacityChanged backgroundOpacityChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(backgroundOpacityChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to BackgroundOpacityChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnBackgroundOpacityChanged)
{
    BackgroundOpacityChanged backgroundOpacityChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(backgroundOpacityChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to BackgroundOpacityChanged";
}

struct ClosedCaptionEnabledChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnEnabledChangedNotification
{
    void onEnabledChanged(const bool) override;
};

void ClosedCaptionEnabledChanged::onEnabledChanged(const bool)
{
    std::cout << "onEnabledChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnEnabledChanged)
{
    ClosedCaptionEnabledChanged ccEnabledChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(ccEnabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnEnabledChanged)
{
    ClosedCaptionEnabledChanged ccEnabledChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(ccEnabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledChanged";
}

struct FontColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontColorChangedNotification
{
    void onFontColorChanged(const std::string &) override;
};

void FontColorSettings::onFontColorChanged(const std::string &color)
{
    std::cout << "onFontColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontColorChanged)
{
    FontColorSettings fontColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontColorChanged)
{
    FontColorSettings fontColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontColorSettings";
}

struct FontEdgeSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontEdgeChangedNotification
{
    void onFontEdgeChanged(const Firebolt::Accessibility::FontEdge &) override;
};

void FontEdgeSettings::onFontEdgeChanged(const Firebolt::Accessibility::FontEdge &edge)
{
    std::cout << "onFontEdgeChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnFontEdgeChanged)
{
    FontEdgeSettings fontEdgeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontEdgeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontEdgeSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontEdgeChanged)
{
    FontEdgeSettings fontEdgeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontEdgeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontEdgeSettings";
}

struct FontEdgeColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontEdgeColorChangedNotification
{
    void onFontEdgeColorChanged(const std::string &) override;
};

void FontEdgeColorSettings::onFontEdgeColorChanged(const std::string &color)
{
    std::cout << "onFontEdgeColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontEdgeColorChanged)
{
    FontEdgeColorSettings fontEdgeColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontEdgeColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontEdgeColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontEdgeColorChanged)
{
    FontEdgeColorSettings fontEdgeColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontEdgeColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontEdgeColorSettings";
}

struct FontFamilySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification
{
    void onFontFamilyChanged(const Firebolt::Accessibility::FontFamily &) override;
};

void FontFamilySettings::onFontFamilyChanged(const Firebolt::Accessibility::FontFamily &family)
{
    std::cout << "onFontFamilyChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnFontFamilyChanged)
{
    FontFamilySettings fontFamilySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontFamilySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontFamilySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontFamilyChanged)
{
    FontFamilySettings fontFamilySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontFamilySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontFamilySettings";
}

struct FontOpacitySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontOpacityChangedNotification
{
    void onFontOpacityChanged(const float) override;
};

void FontOpacitySettings::onFontOpacityChanged(const float opacity)
{
    std::cout << "onFontOpacityChanged event fired with opacity: " << opacity;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontOpacityChanged)
{
    FontOpacitySettings fontOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontOpacitySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontOpacityChanged)
{
    FontOpacitySettings fontOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontOpacitySettings";
}

struct FontSizeSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontSizeChangedNotification
{
    void onFontSizeChanged(const float) override;
};

void FontSizeSettings::onFontSizeChanged(const float size)
{
    std::cout << "onFontSizeChanged event fired with size: " << size;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontSizeChanged)
{
    FontSizeSettings fontSizeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontSizeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontSizeSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontSizeChanged)
{
    FontSizeSettings fontSizeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontSizeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontSizeSettings";
}

struct PreferredLanguagesSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnPreferredLanguagesChangedNotification
{
    void onPreferredLanguagesChanged(const std::vector<std::string> &) override;
};

void PreferredLanguagesSettings::onPreferredLanguagesChanged(const std::vector<std::string> &languages)
{
    std::cout << "onPreferredLanguagesChanged event fired with languages: ";
    for (const auto &lang : languages)
    {
        std::cout << lang << " ";
    }
    std::cout << std::endl;
}

TEST_F(ClosedCaptionsTest, subscribeOnPreferredLanguagesChanged)
{
    PreferredLanguagesSettings preferredLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(preferredLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PreferredLanguagesSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnPreferredLanguagesChanged)
{
    PreferredLanguagesSettings preferredLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(preferredLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PreferredLanguagesSettings";
}

struct TextAlignSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnTextAlignChangedNotification
{
    void onTextAlignChanged(const std::string &) override;
};

void TextAlignSettings::onTextAlignChanged(const std::string &alignment)
{
    std::cout << "onTextAlignChanged event fired with alignment: " << alignment;
}

TEST_F(ClosedCaptionsTest, subscribeOnTextAlignChanged)
{
    TextAlignSettings textAlignSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(textAlignSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TextAlignSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnTextAlignChanged)
{
    TextAlignSettings textAlignSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(textAlignSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TextAlignSettings";
}

struct TextAlignVerticalSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnTextAlignVerticalChangedNotification
{
    void onTextAlignVerticalChanged(const std::string &) override;
};

void TextAlignVerticalSettings::onTextAlignVerticalChanged(const std::string &alignment)
{
    std::cout << "onTextAlignVerticalChanged event fired with alignment: " << alignment;
}

TEST_F(ClosedCaptionsTest, subscribeOnTextAlignVerticalChanged)
{
    TextAlignVerticalSettings textAlignVerticalSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(textAlignVerticalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TextAlignVerticalSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnTextAlignVerticalChanged)
{
    TextAlignVerticalSettings textAlignVerticalSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(textAlignVerticalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TextAlignVerticalSettings";
}

struct WindowColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnWindowColorChangedNotification
{
    void onWindowColorChanged(const std::string &) override;
};

void WindowColorSettings::onWindowColorChanged(const std::string &color)
{
    std::cout << "onWindowColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnWindowColorChanged)
{
    WindowColorSettings windowColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(windowColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to WindowColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnWindowColorChanged)
{
    WindowColorSettings windowColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(windowColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to WindowColorSettings";
}

struct WindowOpacitySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnWindowOpacityChangedNotification
{
    void onWindowOpacityChanged(const float) override;
};

void WindowOpacitySettings::onWindowOpacityChanged(const float opacity)
{
    std::cout << "onWindowOpacityChanged event fired with opacity: " << opacity;
}

TEST_F(ClosedCaptionsTest, subscribeOnWindowOpacityChanged)
{
    WindowOpacitySettings windowOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(windowOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to WindowOpacitySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnWindowOpacityChanged)
{
    WindowOpacitySettings windowOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(windowOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to WindowOpacitySettings";
}
