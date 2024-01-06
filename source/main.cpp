#include <iostream>
#include <nds.h>
#include <maxmod9.h>
#include "soundbank_bin.h"

#include "game.hpp"

int main() {
    irqEnable(IRQ_VBLANK);
    setupTime();

    mmInitDefaultMem((mm_addr)soundbank_bin);

    Game::start();

    return 0;
}
