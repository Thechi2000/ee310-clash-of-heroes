#pragma once
#include <nds.h>

#include "time.hpp"

struct Vector {
    int x, y;
};

struct Sprite {
    void* data;
    uint32_t length;
};

#define TO_BE_IMPLEMENTED() assert(0)

#define IN_RANGE(x, min, max) ((min) <= (x) && (x) <= (max))
