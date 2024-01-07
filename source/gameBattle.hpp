#pragma once
#include "game.hpp"
#include "player.hpp"

class GameBattle : public GameState {
public:
    GameBattle(Faction firstPlayer, Faction secondPlayer);
    ~GameBattle();

    void render();
    GameState* handle_inputs();

    virtual void init();
    virtual void deinit();

private:
    Player playerA_;
    Player playerB_;
};