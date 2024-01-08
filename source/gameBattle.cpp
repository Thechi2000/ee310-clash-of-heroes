#include "gameBattle.hpp"
#include "soundbank.h"
#include <maxmod9.h>

GameBattle::GameBattle(Faction firstPlayer, Faction secondPlayer) :
    playerA_(firstPlayer, false),
    playerB_(secondPlayer, true),
    playerAPlaying_(true) { }
GameBattle::~GameBattle() { }

Player& GameBattle::currentPlayer() {
    return playerAPlaying_ ? playerA_ : playerB_;
}

void GameBattle::init() {
    // Reset the timer to match with game time
    resetTime();

    // Load the music and sound effects
    mmLoad(MOD_BATTLE);
    mmLoadEffect(SFX_BATTLE_ENEMY_HIT);
    mmLoadEffect(SFX_BATTLE_UNIT_APPEARING);
    mmLoadEffect(SFX_BATTLE_UNIT_HIT);
    mmLoadEffect(SFX_BATTLE_UNIT_KILLED);
    mmLoadEffect(SFX_BATTLE_WALL_APPEARING);
    mmLoadEffect(SFX_BATTLE_WALL_HIT);
    mmLoadEffect(SFX_BATTLE_WALL_KILLED);

    // Start the battle music
    mmStart(MOD_BATTLE, MM_PLAY_LOOP);

    // Init both player's screens
    playerA_.init();
    playerB_.init();
}
void GameBattle::deinit() {
    // Unload the battle's music and sound effects
    mmUnload(MOD_BATTLE);
    mmUnloadEffect(SFX_BATTLE_ENEMY_HIT);
    mmUnloadEffect(SFX_BATTLE_UNIT_APPEARING);
    mmUnloadEffect(SFX_BATTLE_UNIT_HIT);
    mmUnloadEffect(SFX_BATTLE_UNIT_KILLED);
    mmUnloadEffect(SFX_BATTLE_WALL_APPEARING);
    mmUnloadEffect(SFX_BATTLE_WALL_HIT);
    mmUnloadEffect(SFX_BATTLE_WALL_KILLED);
}

void GameBattle::render() {
    playerA_.render();
    playerB_.render();
}

GameState* GameBattle::handle_inputs() {
    // Make the current player handle the inputs, and switch the turn to the other player if he as finished
    if (currentPlayer().handleInputs()) {
        playerAPlaying_ = !playerAPlaying_;
    }

    return nullptr;
}
