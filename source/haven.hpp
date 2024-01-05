#pragma once
#include "units.hpp"

// TODO : Assign the right sprite id

class Swordsman : public CoreUnit
{
public:
    Swordsman() : CoreUnit(3, 11, 3, 0) {};
};

class Archer : public CoreUnit
{
public:
    Archer() : CoreUnit(2, 8, 3, 0) {};
};

class Spearman : public CoreUnit
{
public:
    Spearman() : CoreUnit(3, 9, 2, 0) {};
};

class Knight : public EliteUnit
{
public:
    Knight() : EliteUnit(4, 30, 6, 0) {};
};

class Angel : public ChampionUnit
{
public:
    Angel() : ChampionUnit(6, 115, 23, 0) {};
};
