#include "units.hpp"
#include <cmath>
#include <array>
#include "player.hpp"

int Unit::getSpriteIdAt(const Vector& position) {
    if (!IN_RANGE(position.x, 0, size_.x - 1) || !IN_RANGE(position.y, 0, size_.y - 1)) {
        return -1;
    } else {
        return spriteId_ + static_cast<int>(colorType_) * size_.x * size_.y + position.x * size_.y + position.y;
    }
}