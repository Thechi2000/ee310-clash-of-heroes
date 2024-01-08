#pragma once
#include "game.hpp"
#include "player.hpp"

class Player;

class GameBattle : public GameState {
public:
    GameBattle();
    ~GameBattle() { }    

    void render();
    GameState* handle_inputs();

private:
    Player* playerA_;
    Player* playerB_;

    int secondsPassed_;
};