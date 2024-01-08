#pragma once
#include "units.hpp"
#include "army.hpp"

namespace haven {

/**
 * Resistant core unit from Haven
*/
class Swordsman : public CoreUnit {
public:
    Swordsman(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 11, 3, currentPlayer, UnitType::Swordsman, colorType, 3) { };
};

/**
 * Fast core unit from Haven
*/
class Archer : public CoreUnit {
public:
    Archer(Player* currentPlayer, ColorType colorType) : CoreUnit(2, 8, 3, currentPlayer, UnitType::HavenArcher, colorType, 9) { };
};

/**
 * Core unit from Haven, deals its damages before taking them back (and thus not taking them if they kill the unit)
*/
class Spearman : public CoreUnit {
public:
    Spearman(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 9, 2, currentPlayer, UnitType::Spearman, colorType, 6) { };
    int attack(BattleField& opponentBattlefield, int attackedColumn);
};

/**
 * Elite Unit from Haven, starts full charged but do not gain health while charging
*/
class Knight : public EliteUnit {
public:
    Knight(Player* currentPlayer, ColorType colorType) : EliteUnit(4, 30, 6, currentPlayer, UnitType::Knight, colorType, 12) { };
    void onTransformToAttack();
    bool updateCharge();
};

/**
 * Champion Unit from Haven, heals every ally units while charging
*/
class Angel : public ChampionUnit {
public:
    Angel(Player* currentPlayer, ColorType colorType) : ChampionUnit(6, 115, 23, currentPlayer, UnitType::Angel, colorType, 24) { };
    bool updateCharge();
};

/**
 * Strongest wall of the whole game
*/
class HavenWall : public Wall {
public:
    HavenWall(Player* currentPlayer) : Wall(8, currentPlayer, UnitType::HavenWall, 1) { };
};
}