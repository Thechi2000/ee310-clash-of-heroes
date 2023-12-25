#include "utils.hpp"

#include <iostream>

#define DEBUG

class GameState : public Renderable, public InputHandler {

};

class Menu : public GameState {
    virtual void render(const RenderContext& context) const {
#ifndef DEBUG
        TO_BE_IMPLEMENTED();
#else
        std::cout << "Currently in a menu" << std::endl;
#endif
    }

    virtual void handle_inputs() {
        auto keys = keysHeld();

        if (keys & KEY_UP) {
            std::cout << "KEY_UP is down" << std::endl;
        }
    }
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
