#pragma once
#include "units.hpp"

// TODO : Assign the right sprite id

class Swordsman : public CoreUnit
{
public:
    Swordsman(BattleField &currentBattlefield) : CoreUnit(3, 11, 3, currentBattlefield, 0) {};
};

class Archer : public CoreUnit
{
public:
    Archer(BattleField &currentBattlefield) : CoreUnit(2, 8, 3, currentBattlefield, 0) {};
};

class Spearman : public CoreUnit
{
public:
    Spearman(BattleField &currentBattlefield) : CoreUnit(3, 9, 2, currentBattlefield, 0) {};
    int attack(BattleField& opponentBattlefield, int attackedColumn);
};

class Knight : public EliteUnit
{
public:
    Knight(BattleField &currentBattlefield) : EliteUnit(4, 30, 6, currentBattlefield, 0) {};
    void onTransformToAttack();
    bool updateCharge();
};

class Angel : public ChampionUnit
{
public:
    Angel(BattleField &currentBattlefield) : ChampionUnit(6, 115, 23, currentBattlefield, 0) {};
    bool updateCharge();
};
