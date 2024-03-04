#pragma once
#include "Global.h"

std::string defaultLanguage_en_US = R"(
    command.floatingtext.reload=已重载全部悬浮字！\n当前加载了 %1$s 个静态悬浮字和 %2$s 个动态悬浮字。
    command.floatingtext.description=创建悬浮字
    command.error.invalidCommandOrigin=This command can only be executed by the player!
    command.createStatic.success=已成功在 %1$s 的 %2$s 创建静态悬浮字。
    command.createDynamic.success=已成功在 %1$s 的 %2$s 创建更新周期为 %3$ss 的动态悬浮字。
)";

std::string defaultLanguage_zh_CN = R"(
    command.floatingtext.reload=已重载全部悬浮字！\n当前加载了 %1$s 个静态悬浮字和 %2$s 个动态悬浮字。
    command.floatingtext.description=创建悬浮字
    command.error.invalidCommandOrigin=该命令只能由玩家或控制台执行！
    command.createStatic.success=已成功在 %1$s 的 %2$s 创建静态悬浮字。
    command.createDynamic.success=已成功在 %1$s 的 %2$s 创建更新周期为 %3$ss 的动态悬浮字。
)";