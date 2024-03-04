#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace FloatingText {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace FloatingText
