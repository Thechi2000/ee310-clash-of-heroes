#include <iostream>
#include <nds.h>

#include "game.hpp"

int main() {
    irqEnable(IRQ_VBLANK);
    setupTime();
    Game::start();
    return 0;
}
