#pragma once

#include "Config.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>

#include <GMLIB/Files/Language/I18n/LangI18n.h>

namespace FloatingText {

class Entry {

public:
    static Entry& getInstance();

    Entry() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the plugin is loaded successfully.
    bool load();

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

    // /// @return True if the plugin is unloaded successfully.
    bool unload();

    Config& getConfig();

    GMLIB::Files::I18n::LangI18n& getI18n();

private:
    ll::mod::NativeMod&                         mSelf;
    std::optional<Config>                       mConfig;
    std::optional<GMLIB::Files::I18n::LangI18n> mI18n;
};

} // namespace FloatingText
