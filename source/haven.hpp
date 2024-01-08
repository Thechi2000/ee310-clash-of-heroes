#pragma once
#include "units.hpp"
#include "army.hpp"

// TODO : Assign the right sprite id

class Swordsman : public CoreUnit
{
public:
    Swordsman(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 11, 3, currentPlayer, UnitType::Swordsman, colorType, 0) {};
};

class Archer : public CoreUnit
{
public:
    Archer(Player* currentPlayer, ColorType colorType) : CoreUnit(2, 8, 3, currentPlayer, UnitType::Archer, colorType, 0){};
};

class Spearman : public CoreUnit
{
public:
    Spearman(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 9, 2, currentPlayer, UnitType::Spearman, colorType, 0){};
    int attack(BattleField &opponentBattlefield, int attackedColumn);
};

class Knight : public EliteUnit
{
public:
    Knight(Player* currentPlayer, ColorType colorType) : EliteUnit(4, 30, 6, currentPlayer, UnitType::Knight, colorType, 0){};
    void onTransformToAttack();
    bool updateCharge();
};

class Angel : public ChampionUnit
{
public:
    Angel(Player* currentPlayer, ColorType colorType) : ChampionUnit(6, 115, 23, currentPlayer, UnitType::Angel, colorType, 0){};
    bool updateCharge();
};

class HavenWall : public Wall
{
public:
    HavenWall(Player* currentPlayer) : Wall(8, currentPlayer, UnitType::Haven_Wall, 0){};
};