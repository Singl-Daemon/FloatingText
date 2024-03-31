#include "Global.h"
#include <regex>

bool isNumber(const std::string& s) {
    std::regex pattern("[-+]?[0-9]*\\.?[0-9]+");
    return std::regex_match(s, pattern);
}

void invalidInputForm(Player& pl, std::string reason) {
    auto fm = ll::form::ModalForm(
        tr("form.invalidInput.title"),
        tr("form.invalidInput.content", {reason}),
        tr("form.invalidInput.return"),
        tr("form.invalidInput.exit")
    );
    fm.sendTo(pl, [](Player& pl, ll::form::ModalFormResult result, ll::form::FormCancelReason) {
        if (result == ll::form::ModalFormSelectedButton::Upper) {
            return addForm(pl);
        }
        return pl.sendMessage(tr("form.closed"));
    });
}

void dynamicForm(Player& pl, std::string text, Vec3 pos, int dimId) {
    auto fm = ll::form::CustomForm(tr("form.dynamic.title"));
    fm.appendLabel(tr("form.dynamic.lable"));
    fm.appendInput("rate", tr("form.dynamic.rate"), tr("form.dynamic.rate"));
    fm.sendTo(pl, [text, pos, dimId](Player& pl, const ll::form::CustomFormResult& result, ll::form::FormCancelReason) {
        if (!result.has_value()) {
            return addForm(pl);
        }
        std::string srate = std::get<std::string>(result->at("rate"));
        if (isNumber(srate)) {
            int rate = std::stoi(srate);
            createDynamicFloatingText(text, pos, dimId, rate);
            return pl.sendMessage(
                tr("command.createDynamic.success", {VanillaDimensions::toString(dimId), pos.toString(), srate})
            );
        } else {
            return invalidInputForm(pl, tr("form.invalidInput.rate"));
        }
    });
}

void addForm(Player& pl) {
    auto fm = ll::form::CustomForm(tr("form.add.title"));
    fm.appendLabel(tr("form.add.lable"));
    fm.appendInput("text", tr("form.add.text"), tr("form.add.text"));
    fm.appendInput("pos.x", tr("form.add.pos.x"), tr("form.add.pos.x"), S(pl.getPosition().x));
    fm.appendInput("pos.y", tr("form.add.pos.y"), tr("form.add.pos.y"), S(pl.getPosition().y));
    fm.appendInput("pos.z", tr("form.add.pos.z"), tr("form.add.pos.z"), S(pl.getPosition().z));
    fm.appendInput("pos.d", tr("form.add.pos.d"), tr("form.add.pos.d"), S(pl.getDimensionId().id));
    fm.appendToggle("dynamic", tr("form.add.isDynamic"), false);
    fm.sendTo(pl, [](Player& pl, const ll::form::CustomFormResult& result, ll::form::FormCancelReason) {
        if (!result.has_value()) {
            return pl.sendMessage(tr("form.closed"));
        }
        std::string text = std::get<std::string>(result->at("text"));
        if (text.empty()) {
            return invalidInputForm(pl, tr("form.invalidInput.text"));
        }
        ll::string_utils::replaceAll(text, "\\n", "\n");
        std::string sx      = std::get<std::string>(result->at("pos.x"));
        std::string sy      = std::get<std::string>(result->at("pos.y"));
        std::string sz      = std::get<std::string>(result->at("pos.z"));
        std::string sd      = std::get<std::string>(result->at("pos.d"));
        uint64      dynamic = std::get<uint64_t>(result->at("dynamic"));
        if (isNumber(sx) && isNumber(sy) && isNumber(sz) && isNumber(sd)) {
            float x = std::stof(sx);
            float y = std::stof(sy);
            float z = std::stof(sz);
            int   d = std::stoi(sd);
            Vec3  pos{x, y, z};
            if (dynamic) {
                return dynamicForm(pl, text, pos, d);
            } else {
                createStaticFloatingText(text, pos, d);
                return pl.sendMessage(
                    tr("command.createStatic.success", {VanillaDimensions::toString(d), pos.toString()})
                );
            }
        } else {
            return invalidInputForm(pl, tr("form.invalidInput.pos"));
        }
    });
}