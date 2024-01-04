#include "gameBattle.hpp"
#include "sylvanBg.h"
#include "sylvanUnits.h"
GameBattle::GameBattle() { }

void GameBattle::render() {
    playerA_.render();
    playerB_.render();
}

GameState* GameBattle::handle_inputs() {
    return nullptr;
}