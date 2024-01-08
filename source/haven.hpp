#pragma once
#include "units.hpp"
#include "army.hpp"

// TODO : Assign the right sprite id

class Swordsman : public CoreUnit
{
public:
    Swordsman(Player* currentPlayer) : CoreUnit(3, 11, 3, currentPlayer, UnitType::Swordsman, 0) {};
};

class Archer : public CoreUnit
{
public:
    Archer(Player* currentPlayer) : CoreUnit(2, 8, 3, currentPlayer, UnitType::Archer, 0){};
};

class Spearman : public CoreUnit
{
public:
    Spearman(Player* currentPlayer) : CoreUnit(3, 9, 2, currentPlayer, UnitType::Spearman, 0){};
    int attack(BattleField &opponentBattlefield, int attackedColumn);
};

class Knight : public EliteUnit
{
public:
    Knight(Player* currentPlayer) : EliteUnit(4, 30, 6, currentPlayer, UnitType::Knight, 0){};
    void onTransformToAttack();
    bool updateCharge();
};

class Angel : public ChampionUnit
{
public:
    Angel(Player* currentPlayer) : ChampionUnit(6, 115, 23, currentPlayer, UnitType::Angel, 0){};
    bool updateCharge();
};

class HavenWall : public Wall
{
    HavenWall(int health, Player* currentPlayer) : Wall(8, currentPlayer, UnitType::Haven_Wall, 0){};
};