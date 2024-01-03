#pragma once
#include <nds.h>
#include <optional>

struct Vector {
    int x, y;
};

struct Sprite {
    void* data;
    uint32_t length;
};

#define TO_BE_IMPLEMENTED() assert(0)

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

static inline std::optional<Direction> from_keys(int keys) {
    if (keys & KEY_UP) {
        return Direction::UP;
    } else if (keys & KEY_RIGHT) {
        return Direction::RIGHT;
    } else if (keys & KEY_DOWN) {
        return Direction::DOWN;
    } else if (keys & KEY_LEFT) {
        return Direction::LEFT;
    }

    return {};
}

#define IN_RANGE(x, min, max) ((min) <= (x) && (x) <= (max))