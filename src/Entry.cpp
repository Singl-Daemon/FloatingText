#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace FloatingText {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() {
    initConfig();
    return true;
}

bool Entry::enable() {
    initFloatingTexts();
    RegisterCommand();
    logger.info(tr("info.loaded"));
    logger.info("{}: GroupMountain", tr("info.author"));
    logger.info("{}: https://github.com/GroupMountain/FloatingText", tr("info.repository"));
    return true;
}

bool Entry::disable() {
    removeAllFloatingTexts();
    return true;
}

bool Entry::unload() {
    getInstance().reset();
    return true;
}

} // namespace FloatingText

LL_REGISTER_PLUGIN(FloatingText::Entry, FloatingText::Entry::getInstance());