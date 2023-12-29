#pragma once
#include "utils.hpp"
#include <iostream>

#define DEBUG

class GameState {
public:
    virtual void render() = 0;
    virtual void handle_inputs() = 0;
};

class Game {
public:
    Game();

    static void start() {
        Game game;
        while (1) {
            game.update();
            swiWaitForVBlank();
        }
    }

    void update();

private:
    GameState* game_state_;
};
