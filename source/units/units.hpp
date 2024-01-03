#pragma once
#include "game.hpp"

struct Faction;

// ---------------------------------------------------------------------- //

class Unit
{
public:
    virtual int disappear() { return 0; } // return damage dealt
    virtual void transformToWall() = 0;
    virtual void transformToAtack() = 0;
    const Vector &getSize() const { return size_; }

protected:
    Unit(int width, int length) : size_{.x = width, .y = length} {}
    Unit(Vector size) : size_(size) {}

private:
    Vector size_;
    int health_;
    bool is_charging_;
    int charge_;
    // TODO Faction faction_;
    Sprite neutralSprites_;
};

class SpecialUnit : public Unit
{
protected:
    SpecialUnit(int width) : Unit(width, 2){};
};

// ---------------------------------------------------------------------- //

class CoreUnit : public Unit
{
protected:
    CoreUnit() : Unit(1, 1){};
};

class EliteUnit : public SpecialUnit
{
protected:
    EliteUnit() : SpecialUnit(1){};
};

class ChampionUnit : public SpecialUnit
{
protected:
    ChampionUnit() : SpecialUnit(2){};
};

// ---------------------------------------------------------------------- //

class Wall : public Unit
{
public:
    virtual void onCreation(){};
    virtual void onDestroy(){};
    virtual void onCombination(){};

protected:
    Wall(Sprite weakWalls, Sprite strongWalls, int maxHealth) : Unit(1, 1), weakWalls_(weakWalls), strongWalls_(strongWalls), maxHealth_(maxHealth) {}

private:
    Sprite weakWalls_;
    Sprite strongWalls_;
    int maxHealth_;
};
