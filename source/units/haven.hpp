#pragma once
#include "units.hpp"

class Swordsman : public CoreUnit
{
public:
    Swordsman() : CoreUnit(){};
};

class Archer : public CoreUnit
{
public:
    Archer() : CoreUnit(){};
};

class Spearman : public CoreUnit
{
public:
    Spearman() : CoreUnit(){};
};

class Knight : public EliteUnit
{
public:
    Knight() : EliteUnit(){};
};

class Angel : public ChampionUnit
{
public:
    Angel() : ChampionUnit(){};
};