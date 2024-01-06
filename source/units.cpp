#include "units.hpp"
#include <cmath>
#include <array>

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

int ChampionUnit::attack(BattleField& opponentBattlefield, int attackedColumn) {
    if (!is_charging_) {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8) {
        Unit* u1 = opponentBattlefield[i];
        health_ -= u1->disappear();
        Unit* u2 = opponentBattlefield[i + 8];
        health_ -= u2->disappear();
        delete u1;
        delete u2;
        opponentBattlefield[i] = nullptr;
        opponentBattlefield[i + 8] = nullptr;
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

void Unit::heal() {
    float maxCurrentHealth = (power_ - toughness_) * (1 - remainingChargeTurns_ / charge_);
    float heal = (power_ - toughness_) / charge_;

    health_ = std::min(maxCurrentHealth, health_ + heal);
}