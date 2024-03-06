#include "Config.h"
#include "Global.h"
#include "Language.h"

GMLIB::Files::JsonConfig*     Config                 = nullptr;
GMLIB::Files::I18n::LangI18n* Language               = nullptr;
int                           commandPermissionLevel = 4;

nlohmann::json StaticFloatingTextList;
nlohmann::json DynamicFloatingTextList;

std::unordered_map<int64, GMLIB::Server::FloatingText*> RuntimeFloatingTexts;

void initConfig() {
    Config = new GMLIB::Files::JsonConfig("./plugins/FloatingText/config/config.json", defaultConfig);
    Config->init();
    std::string langPath     = "./plugins/FloatingText/language/";
    std::string languageCode = Config->getValue<std::string>({"language"}, "en_US");
    Language                 = new GMLIB::Files::I18n::LangI18n(langPath, languageCode);
    Language->updateOrCreateLanguage("en_US", defaultLanguage_en_US);
    Language->updateOrCreateLanguage("zh_CN", defaultLanguage_zh_CN);
    Language->loadAllLanguages();
    Language->chooseLanguage(languageCode);
}

void initFloatingTexts() {
    StaticFloatingTextList =
        GMLIB::Files::JsonFile::initJson("./plugins/FloatingText/config/StaticFloatingText.json", defaultStaticFile);
    for (auto& config : StaticFloatingTextList) {
        auto text  = GMLIB::Files::JsonFile::getValue<std::string>(config, {"Text"}, "");
        auto x     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "x"}, 0);
        auto y     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "y"}, 0);
        auto z     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "z"}, 0);
        auto dimid = GMLIB::Files::JsonFile::getValue<int>(config, {"Position", "dim"}, 0);
        Vec3 pos{x, y, z};
        auto ft = new GMLIB::Server::StaticFloatingText(text, pos, dimid, true);
        // Static
        RuntimeFloatingTexts[ft->getRuntimeID()] = ft;
    }
    DynamicFloatingTextList =
        GMLIB::Files::JsonFile::initJson("./plugins/FloatingText/config/DynamicFloatingText.json", defaultDynamicFile);
    for (auto& config : DynamicFloatingTextList) {
        auto text   = GMLIB::Files::JsonFile::getValue<std::string>(config, {"Text"}, "");
        auto x      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "x"}, 0);
        auto y      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "y"}, 0);
        auto z      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "z"}, 0);
        auto dimid  = GMLIB::Files::JsonFile::getValue<int>(config, {"Position", "dim"}, 0);
        auto update = GMLIB::Files::JsonFile::getValue<int>(config, {"UpdateRate"}, 1);
        Vec3 pos{x, y, z};
        auto ft = new GMLIB::Server::DynamicFloatingText(text, pos, dimid, update, true);
        // Dynamic
        RuntimeFloatingTexts[ft->getRuntimeID()] = ft;
    }
}

void removeAllFloatingTexts() {
    for (auto& key : RuntimeFloatingTexts) {
        delete key.second;
    }
    RuntimeFloatingTexts.clear();
}

std::pair<int, int> getFloatingTextCount() { return {StaticFloatingTextList.size(), DynamicFloatingTextList.size()}; }

std::string tr(std::string key, std::vector<std::string> data) { return Language->translate(key, data); }

void createStaticFloatingText(std::string& text, Vec3& pos, int dimId) {
    nlohmann::json json{
        {"Text",     text                                                      },
        {"Position", {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}, {"dim", dimId}}}
    };
    auto ft = new GMLIB::Server::StaticFloatingText(text, pos, dimId, true);
    StaticFloatingTextList.push_back(json);
    std::string path = "./plugins/FloatingText/config/StaticFloatingText.json";
    GMLIB::Files::JsonFile::writeFile(path, StaticFloatingTextList);
    RuntimeFloatingTexts[ft->getRuntimeID()] = ft;
}

void createDynamicFloatingText(std::string& text, Vec3& pos, int dimId, int update) {
    nlohmann::json json{
        {"Text",       text                                                      },
        {"UpdateRate", update                                                    },
        {"Position",   {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}, {"dim", dimId}}}
    };
    auto ft = new GMLIB::Server::DynamicFloatingText(text, pos, dimId, update, true);
    DynamicFloatingTextList.push_back(json);
    std::string path = "./plugins/FloatingText/config/DynamicFloatingText.json";
    GMLIB::Files::JsonFile::writeFile(path, DynamicFloatingTextList);
    RuntimeFloatingTexts[ft->getRuntimeID()] = ft;
}