#pragma once
#pragma warning(disable : 4267)

#include <include_all.h>

#define PLUGIN_NAME "FloatingText"
#define S(x)        std::to_string(x)

extern ll::Logger logger;

extern void removeAllFloatingTexts();
extern void initConfig();
extern void initFloatingTexts();
extern void RegisterCommand();

extern std::pair<int, int> getFloatingTextCount();

extern void createStaticFloatingText(std::string const& text, Vec3 const& pos, int dimId);
extern void createDynamicFloatingText(std::string const& text, Vec3 const& pos, int dimId, int update);

extern std::string tr(std::string const& key, std::vector<std::string> const& data = {});

extern void addForm(Player& pl);