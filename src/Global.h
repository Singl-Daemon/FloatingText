#pragma once
#include <include_all.h>

#define PLUGIN_NAME "FloatingText"
#define S(x)        std::to_string(x)

extern ll::Logger logger;

extern void removeAllFloatingTexts();
extern void initConfig();
extern void initFloatingTexts();
extern void RegisterCommand();

extern std::pair<int, int> getFloatingTextCount();

extern void createStaticFloatingText(std::string text, Vec3 pos, int dimId);
extern void createDynamicFloatingText(std::string text, Vec3 pos, int dimId, int update);

extern std::string tr(std::string key, std::vector<std::string> data = {});

extern void addForm(Player& pl);