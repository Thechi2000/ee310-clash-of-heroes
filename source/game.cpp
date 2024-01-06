#include <nds.h>
#include "game.hpp"
#include "menu.hpp"
#include "gameBattle.hpp"


void Game::start() {
    Game game;
    while (1) {
        game.update();
        swiWaitForVBlank();
    }
}

Game::Game() : game_state_(new CharacterSelectionMenu()) { }

void Game::update() {
    scanKeys();

    auto new_game_state = game_state_->handle_inputs();
    if (new_game_state != nullptr) {
        delete game_state_;
        game_state_ = new_game_state;
    }

    game_state_->render();
}