#include "Entry.h"
#include "Global.h"
#include <fmt/format.h>
#include <functional>
#include <ll/api/Config.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/plugin/NativePlugin.h>
#include <ll/api/plugin/PluginManagerRegistry.h>
#include <memory>
#include <stdexcept>
ll::Logger logger(PLUGIN_NAME);

namespace FloatingText {

namespace {

std::unique_ptr<std::reference_wrapper<ll::plugin::NativePlugin>>
    selfPluginInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

auto disable(ll::plugin::NativePlugin& /*self*/) -> bool {
    removeAllFloatingTexts();
    return true;
}

auto enable(ll::plugin::NativePlugin& /*self*/) -> bool {
    initFloatingTexts();
    RegisterCommand();
    return true;
}

auto load(ll::plugin::NativePlugin& self) -> bool {
    selfPluginInstance = std::make_unique<std::reference_wrapper<ll::plugin::NativePlugin>>(self);
    initConfig();
    return true;
}

auto unload(ll::plugin::NativePlugin& self) -> bool {
    selfPluginInstance.reset();
    return true;
}

} // namespace

auto getSelfPluginInstance() -> ll::plugin::NativePlugin& {
    if (!selfPluginInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }

    return *selfPluginInstance;
}

} // namespace FloatingText

extern "C" {
_declspec(dllexport) auto ll_plugin_disable(ll::plugin::NativePlugin& self) -> bool {
    return FloatingText::disable(self);
}
_declspec(dllexport) auto ll_plugin_enable(ll::plugin::NativePlugin& self) -> bool {
    return FloatingText::enable(self);
}
_declspec(dllexport) auto ll_plugin_load(ll::plugin::NativePlugin& self) -> bool { return FloatingText::load(self); }
_declspec(dllexport) auto ll_plugin_unload(ll::plugin::NativePlugin& self) -> bool {
    return FloatingText::unload(self);
}
}
