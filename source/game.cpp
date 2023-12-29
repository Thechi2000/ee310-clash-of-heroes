#include <nds.h>
#include "game.hpp"
#include "menu.hpp"

Game::Game() : game_state_(new CharacterSelectionMenu()) { }

void Game::update() {
    scanKeys();
    game_state_->handle_inputs();
    game_state_->render();
}