#include <nds.h>
#include "game.hpp"

Game::Game() : game_state_(new Menu()) {
#ifdef DEBUG
    consoleDemoInit();
#endif // DEBUG
}

void Game::update() {
#ifdef DEBUG
    consoleClear();
#endif // DEBUG

    scanKeys();
    game_state_->handle_inputs();
    game_state_->render(RenderContext());
}