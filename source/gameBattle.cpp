#include "gameBattle.hpp"
#include "sylvanBg.h"
#include "sylvanUnits.h"
GameBattle::GameBattle(Faction firstPlayer, Faction secondPlayer) :
    playerA_(firstPlayer),
    playerB_(secondPlayer) {
    resetTime();
}

void GameBattle::render() {
    playerA_.render();
    playerB_.render();
}

GameState* GameBattle::handle_inputs() {
    playerA_.handleInputs();
    playerB_.handleInputs();

    return nullptr;
}