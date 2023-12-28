#include "game.hpp"
#include "player.hpp"

class GameBattle : public GameState {

private :
    Player playerA_;
    Player playerB_;

    Sprite backgroundA_;
    Sprite backgroundB_;
};