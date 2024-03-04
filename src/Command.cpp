#include "Global.h"

struct FloatingTextParam {
    enum class GUI { gui } gui;
    enum class Reload { reload } reload;
    enum class Create { createstatic } createstatic;
    enum class Static { createdynamic } createdynamic;
    DimensionType        dimension;
    CommandPositionFloat position;
    std::string          text;
    int                  seconds;
};

void RegisterCommand() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "floatingtext",
        tr("command.floatingtext.description"),
        CommandPermissionLevel::GameDirectors
    );
    ll::service::getCommandRegistry()->registerAlias("floatingtext", "ft");
    cmd.overload<FloatingTextParam>()
        .required("reload")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, FloatingTextParam const& param) {
            removeAllFloatingTexts();
            initFloatingTexts();
            auto count = getFloatingTextCount();
            return output.success(tr("command.floatingtext.reload", {S(count.first), S(count.second)}));
        }>();
    cmd.overload<FloatingTextParam>()
        .required("gui")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, FloatingTextParam const& param) {
            auto type = origin.getOriginType();
            if (type == CommandOriginType::Player) {
                // todo
                return output.success(tr("command.todo"));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
    cmd.overload<FloatingTextParam>()
        .required("createstatic")
        .required("text")
        .required("position")
        .required("dimension")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, FloatingTextParam const& param) {
            auto text  = param.text;
            auto pos   = param.position.mOffset;
            auto dimid = param.dimension;
            createStaticFloatingText(text, pos, dimid);
            auto dimName = VanillaDimensions::toString(param.dimension);
            return output.success(tr("command.createStatic.success", {dimName, pos.toString()}));
        }>();
    cmd.overload<FloatingTextParam>()
        .required("createdynamic")
        .required("text")
        .required("position")
        .required("dimension")
        .required("seconds")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, FloatingTextParam const& param) {
            auto text   = param.text;
            auto pos    = param.position.mOffset;
            auto dimid  = param.dimension;
            auto update = param.seconds;
            createDynamicFloatingText(text, pos, dimid, update);
            auto dimName = VanillaDimensions::toString(param.dimension);
            return output.success(tr("command.createDynamic.success", {dimName, pos.toString(), S(update)}));
        }>();
}