#include <cmath>
#include "player.hpp"
#include "haven.hpp"
#include "utils.hpp"

int Spearman::attack(BattleField &opponentBattlefield, int attackedColumn)
{
    if (!is_charging_)
    {
        return 0;
    }

    int damage = 0;
    int i = 8 * attackedColumn;
    while (damage < health_ && i < 8)
    {
        damage = opponentBattlefield.units[i]->disappear();
        handleDisparition(i, opponentBattlefield);
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

void Knight::onTransformToAttack()
{
    health_ = power_;
    Unit::onTransformToAttack();
}

bool Knight::updateCharge()
{
    float h = health_;
    bool b = Unit::updateCharge();
    health_ = h;
    return b;
}

bool Angel::updateCharge()
{
    BattleField* allyBattlefield = currentPlayer_->getAllyBattlefield();

    for (int i = 0; i < 8 * 6; ++i)
    {
        if (allyBattlefield->unitTypes[i] <= CoreCharging_F && allyBattlefield->unitTypes[i] != None)
        {
            allyBattlefield->units[i]->heal();
        }
    }

    return Unit::updateCharge();
}