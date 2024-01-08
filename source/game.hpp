#pragma once
#include "utils.hpp"
#include <iostream>

#define DEBUG

class GameState {
public:
    virtual ~GameState() { }

    /**
     * Draw the gamestate on the screens
    */
    virtual void render() = 0;
    /**
     * Update the gamestate based on user inputs
    */
    virtual GameState* handle_inputs() = 0;

    /**
     * Set up the NDS peripherals, e.g. setting display's control register, loading music modules or effects, etc.
    */
    virtual void init() = 0;
    /**
     * Free all used peripherals
    */
    virtual void deinit() = 0;

    // Note: the above functions are required (instead of doing it 
    // in constructors/destructors) in order that, when switching between
    // gamestate, the setup of one will not conflict with the removal of
    // another.
};

class Game {
public:
    Game();

    /**
     * Create and run a game to completion
    */
    static void start();
    void update();

private:
    GameState* game_state_;
};
