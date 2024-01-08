#include "units.hpp"
#include <cmath>
#include <array>
#include "player.hpp"

void handleDisparition(int battlefieldPosition, BattleField &battleField) {
    UnitType uT = battleField.unitTypes[battlefieldPosition];

    if (uT == None) {
        return;
    }
    if (uT < SubUnits) {
        int x = battleField.units[battlefieldPosition]->getSize().x;
        int y = battleField.units[battlefieldPosition]->getSize().y;
        delete battleField.units[battlefieldPosition];
        for (int i = 0; i < y; i--) {
            for (int j = 0; j < x; j--) {
                battleField.unitTypes[battlefieldPosition + i + 8*j] = None;
                
                battleField.units[battlefieldPosition + i + 8*j] = nullptr;
            }
        }
        
        return;
    }
    if (uT == CoreCharging_F) {
        delete battleField.units[battlefieldPosition];
        for (int i = 0; i < 3; ++i) {
            battleField.unitTypes[battlefieldPosition + i] = None;
            battleField.units[battlefieldPosition + i] = nullptr;
        }
    }
    if (uT == CoreCharging_B || uT == Elite_B || uT == Champion_LB) {
        return handleDisparition(battlefieldPosition - 1, battleField);
    }
    if (uT == CoreCharging_BB) {
        return handleDisparition(battlefieldPosition - 2, battleField);
    }
    if (uT == Champion_RF) {
        return handleDisparition(battlefieldPosition - 8, battleField);
    }
    if (uT == Champion_RB) {
        return handleDisparition(battlefieldPosition - 9, battleField);
    }

}

int Unit::disappear()
{
    return std::round(health_);
}

void Unit::onTransformToAttack()
{
    is_charging_ = true;
}

bool Unit::updateCharge()
{
    if (!is_charging_)
    {
        return false;
    }

    health_ = (power_ - toughness_) / charge_;
    remainingChargeTurns_ -= 1;

    if (!remainingChargeTurns_)
    {
        std::round(health_);
        return true;
    }
    return false;
}

int Unit::attack(BattleField &opponentBattlefield, int attackedColumn)
{
    if (!is_charging_)
    {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8)
    {
        Unit *u = opponentBattlefield.units[i];
        if (!u) {
            health_ -= u->disappear();
            handleDisparition(i, opponentBattlefield);
        }
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

int ChampionUnit::attack(BattleField &opponentBattlefield, int attackedColumn)
{
    if (!is_charging_)
    {
        return 0;
    }

    int i = 8 * attackedColumn;
    while (health_ > 0 && i < 8)
    {
        Unit *u1 = opponentBattlefield.units[i];
        if (!u1) {
            health_ -= u1->disappear();
            handleDisparition(i, opponentBattlefield);
        }
        Unit *u2 = opponentBattlefield.units[i + 8];
        if (!u2) {
            health_ -= u2->disappear();
            handleDisparition(i + 8, opponentBattlefield);
        }
        ++i;
    }

    disappear();

    return std::max(std::round(health_), 0.0f);
}

void Unit::heal()
{
    if (is_charging_)
    {
        float maxCurrentHealth = (power_ - toughness_) * (1 - remainingChargeTurns_ / charge_);
        float heal = (power_ - toughness_) / charge_;

        health_ = std::min(maxCurrentHealth, health_ + heal);
    }
}