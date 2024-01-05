#pragma once
#include "utils.hpp"
#include <iostream>

#define DEBUG

class GameState {
public:
    virtual ~GameState() {}
    virtual void render() = 0;
    virtual GameState* handle_inputs() = 0;
};

class Game {
public:
    Game();
    static void start();
    void update();

private:
    GameState* game_state_;
};
