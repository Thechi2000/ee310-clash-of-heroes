#pragma once
#include "units.hpp"

enum HavenArmy {
    Swordsman,
    Archer,
    Spearman,
    Knight,
    Angel,
};

class Swordsman : public CoreUnit
{
public:
    Swordsman() : CoreUnit(3, 11, 3) {};
};

class Archer : public CoreUnit
{
public:
    Archer() : CoreUnit(2, 8, 3) {};
};

class Spearman : public CoreUnit
{
public:
    Spearman() : CoreUnit(3, 9, 2) {};
};

class Knight : public EliteUnit
{
public:
    Knight() : EliteUnit(4, 30, 6) {};
};

class Angel : public ChampionUnit
{
public:
    Angel() : ChampionUnit(6, 115, 23) {};
};