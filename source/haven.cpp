#include <cmath>
#include "player.hpp"
#include "haven.hpp"
#include "utils.hpp"

int haven::Spearman::attack(BattleField& opponentBattlefield, int attackedColumn) {
    if (!isCharging_) {
        return 0;
    }

    int damage = 0;
    int i = 8 * attackedColumn;
    while (damage < health_ && i < 8) {
        damage = opponentBattlefield[i]->disappear();
        currentPlayer_->getEnnemy()->handleDisparition(i);
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

void haven::Knight::onTransformToAttack() {
    health_ = power_;
    Unit::onTransformToAttack();
}

bool haven::Knight::updateCharge() {
    float h = health_;
    bool b = Unit::updateCharge();
    health_ = h;
    return b;
}

bool haven::Angel::updateCharge() {
    BattleField& allyBattlefield = currentPlayer_->getAllyBattlefield();

    for (int i = 0; i < 8 * 6; ++i) {
        if (allyBattlefield[i] != nullptr) {
            allyBattlefield[i]->heal();
        }
    }

    return Unit::updateCharge();
}