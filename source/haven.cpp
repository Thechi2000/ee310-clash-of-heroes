#include "haven.hpp"
#include <cmath>
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
        Unit *u = opponentBattlefield[i];
        damage = u->disappear();
        delete u;
        opponentBattlefield[i] = nullptr;
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
    bool ignore[48] = { false };

    for (int i = 0; i < 8 * 6; ++i)
    {
        if (!ignore[i])
        {
            Unit *u = currentBattleField_[i];
            u->heal();

            Vector s = u->getSize();
            for (int x = 0; x < s.x; x++) {
                for (int y = 0; y < s.y; y++) {
                    ignore[i + y + 8 * x] = true;
                }
            }
        }
    }
}