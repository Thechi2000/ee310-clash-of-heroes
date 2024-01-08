#include "gameBattle.hpp"
#include "sylvanBg.h"
#include "sylvanUnits.h"
GameBattle::GameBattle() {
    resetTime();
}

void GameBattle::render() {
    playerA_->render();
    playerB_->render();
}

GameState* GameBattle::handle_inputs() {
    playerA_->handleInputs();
    playerB_->handleInputs();

    return nullptr;
}