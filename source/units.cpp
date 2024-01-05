#include "units.hpp"
#include <cmath>

int Unit::disappear() {
    return std::round(health_);
}

void Unit::onTransformToAttack() {
    is_charging_ = true;
    
}

bool Unit::updateCharge() {
    if (!is_charging_) {
        return false;
    }
    
    health_ = (power_ - toughness_) / charge_;
    remainingChargeTurns_ -= 1;

    if (!remainingChargeTurns_) {
        std::round(health_);
        return true;
    }
    return false;
}

int Unit::attack(BattleField& opponentBattlefield, int attackedColumn) {
    if (!is_charging_) {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8) {
        Unit* u = opponentBattlefield[i];
        health_ -= u->disappear();
        delete u;
        opponentBattlefield[i] = nullptr;
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}