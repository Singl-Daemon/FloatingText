#include "Entry.h"

ll::Logger logger(PLUGIN_NAME);

namespace FloatingText {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() { return true; }

bool Entry::enable() {
    mConfig.emplace();
    if (!ll::config::loadConfig(*mConfig, getSelf().getConfigDir() / u8"config.json")) {
        ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    }
    mI18n.emplace(getSelf().getLangDir(), mConfig->language);
    mI18n->updateOrCreateLanguage("en_US", en_US);
    mI18n->updateOrCreateLanguage("zh_CN", zh_CN);
    mI18n->loadAllLanguages();
    initFloatingTexts();
    RegisterCommand();
    logger.info(tr("info.loaded"));
    logger.info("{}: GroupMountain", tr("info.author"));
    logger.info("{}: https://github.com/GroupMountain/FloatingText", tr("info.repository"));
    return true;
}

bool Entry::disable() {
    removeAllFloatingTexts();
    mConfig.reset();
    mI18n.reset();
    return true;
}

bool Entry::unload() {
    getInstance().reset();
    return true;
}

Config& Entry::getConfig() { return mConfig.value(); }

LangI18n& Entry::getI18n() { return mI18n.value(); }

} // namespace FloatingText

LL_REGISTER_PLUGIN(FloatingText::Entry, FloatingText::Entry::getInstance());

std::string tr(std::string const& key, std::vector<std::string> const& data) {
    return FloatingText::Entry::getInstance()->getI18n().get(key, data);
}