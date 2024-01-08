#include "units.hpp"
#include <cmath>
#include <array>
#include "player.hpp"

int Unit::disappear() {
    return std::round(health_);
}

void Unit::onTransformToAttack() {
    isCharging_ = true;
    fusion_ = 1;
}

void Unit::onFusion(Unit* fusionUnit) {
    ++fusion_;
    health_ += fusionUnit->disappear();
}

bool Unit::updateCharge() {
    if (!isCharging_) {
        return false;
    }

    health_ += fusion_ * (power_ - toughness_) / charge_;
    remainingChargeTurns_ -= 1;

    if (!remainingChargeTurns_) {
        std::round(health_);
        return true;
    }
    return false;
}

int Unit::attack(BattleField& opponentBattlefield, int attackedColumn) {
    if (!isCharging_) {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8) {
        Unit* u = opponentBattlefield[i];
        if (u != nullptr) {
            health_ -= u->disappear();
            currentPlayer_->getEnnemy()->handleDisparition(i);
        }
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

int Unit::getSpriteIdAt(const Vector& position) {
    if (!IN_RANGE(position.x, 0, size_.x - 1) || !IN_RANGE(position.y, 0, size_.y - 1)) {
        return -1;
    } else {
        return spriteId_ + static_cast<int>(colorType_) * size_.x * size_.y + position.x * size_.y + position.y;
    }
}

int ChampionUnit::attack(BattleField& opponentBattlefield, int attackedColumn) {
    if (!isCharging_) {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8) {
        Unit* u1 = opponentBattlefield[i];
        if (u1 != nullptr) {
            health_ -= u1->disappear();
            currentPlayer_->getEnnemy()->handleDisparition(i);
        }
        Unit* u2 = opponentBattlefield[i + 8];
        if (u2 != nullptr) {
            health_ -= u2->disappear();
            currentPlayer_->getEnnemy()->handleDisparition(i + 8);
        }
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

void Unit::heal() {
    if (isCharging_) {
        float maxCurrentHealth = fusion_ * (power_ - toughness_) * (1 - remainingChargeTurns_ / charge_);
        float heal = fusion_ * (power_ - toughness_) / charge_;

        health_ = std::min(maxCurrentHealth, health_ + heal);
    }
}

void Wall::onCombination(Wall* other, int otherBattlefieldPosition) {
    int h = other->disappear();
    delete other;
    currentPlayer_->getAllyBattlefield()[otherBattlefieldPosition] = nullptr;
    health_ = std::min(static_cast<float>(power_), health_ + h);
}