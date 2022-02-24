#include "modInfAllHealth.hpp"
#include "modEnemySpawn.hpp"
#include "../utils/MessageDisplay.hpp" // TODO(): DISPLAY_MESSAGE should probably be included in mod.hpp or something
#include "iostream"
#if 1
bool InfAllHealth::modEnabled{ false };
int InfAllHealth::hotkey{ NULL };
float inputLockoutTimer = 0.0f;

std::optional<std::string> InfAllHealth::onInitialize() {

    return Mod::onInitialize();
}

void InfAllHealth::toggle(bool enable)
{
    if (enable)
    {
        install_patch_offset(0x11BFD9, patchAllHealth, "\xF3\x0F\x5C\xC9", 4);
    }
    else
    {
        patchAllHealth.revert();
    }
}

void InfAllHealth::onGUIframe()
{
    if (ImGui::Checkbox("Infinite Health", &modEnabled))
    {
        toggle(modEnabled);
    }
}

void InfAllHealth::onConfigLoad(const utils::Config& cfg)
{
    modEnabled = cfg.get<bool>("infinite_health_all").value_or(false);
    hotkey = cfg.get<int>("inf_hp_hotkey").value_or(0x70);
    toggle(modEnabled);
};

void InfAllHealth::onConfigSave(utils::Config& cfg)
{
    cfg.set<bool>("infinite_health_all", modEnabled);
    cfg.set<int>("inf_hp_hotkey", hotkey);
};

void InfAllHealth::onUpdateInput(hl::Input& input)
{
    if (!input.isDown(EnemySpawn::hotkeySpawnModifier))
    {
        if (input.wentDown(hotkey)) {
            if (modEnabled) {
                DISPLAY_MESSAGE("Infinite Health Off"); // lmao no format strings for almost a year or when i wrote that shit
            }
            else {
                DISPLAY_MESSAGE("Infinite Health On");
            }
            modEnabled = !modEnabled;
            toggle(modEnabled);
        }
    }
}
#endif