#include "gameBattle.hpp"
#include "soundbank.h"
#include <maxmod9.h>

GameBattle::GameBattle(Faction firstPlayer, Faction secondPlayer) : playerA_(firstPlayer), playerB_(secondPlayer)
{
}
GameBattle::~GameBattle() {}

void GameBattle::init()
{
    resetTime();

    mmLoad(MOD_BATTLE);
    mmLoadEffect(SFX_BATTLE_ENEMY_HIT);
    mmLoadEffect(SFX_BATTLE_UNIT_APPEARING);
    mmLoadEffect(SFX_BATTLE_UNIT_HIT);
    mmLoadEffect(SFX_BATTLE_UNIT_KILLED);
    mmLoadEffect(SFX_BATTLE_WALL_APPEARING);
    mmLoadEffect(SFX_BATTLE_WALL_HIT);
    mmLoadEffect(SFX_BATTLE_WALL_KILLED);

    mmStart(MOD_BATTLE, MM_PLAY_LOOP);

    playerA_.init();
    playerB_.init();
}
void GameBattle::deinit()
{
    mmUnload(MOD_BATTLE);
    mmUnloadEffect(SFX_BATTLE_ENEMY_HIT);
    mmUnloadEffect(SFX_BATTLE_UNIT_APPEARING);
    mmUnloadEffect(SFX_BATTLE_UNIT_HIT);
    mmUnloadEffect(SFX_BATTLE_UNIT_KILLED);
    mmUnloadEffect(SFX_BATTLE_WALL_APPEARING);
    mmUnloadEffect(SFX_BATTLE_WALL_HIT);
    mmUnloadEffect(SFX_BATTLE_WALL_KILLED);
}

void GameBattle::render()
{
    playerA_.render();
    playerB_.render();
}

GameState *GameBattle::handle_inputs()
{
    playerA_.handleInputs();
    playerB_.handleInputs();

    return nullptr;
}
