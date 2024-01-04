#pragma once
#include "game.hpp"

struct Faction;

// ---------------------------------------------------------------------- //

class Unit {
public:
    virtual ~Unit() { }

    virtual int disappear() { return 0; } // return damage dealt
    virtual void transformToWall() = 0;
    virtual void transformToAtack() = 0;
    const Vector& getSize() const { return size_; }

    int getSpriteIdAt(const Vector& position) {
        if (!IN_RANGE(position.x, 0, size_.x - 1) || !IN_RANGE(position.y, 0, size_.y - 1)) {
            return -1;
        } else {
            return spriteId_ + position.x * size_.y + position.y;
        }
    }

protected:
    Unit(int width, int length, int spriteId) : size_{ .x = width, .y = length }, spriteId_(spriteId) { }
    Unit(Vector size, int spriteId) : size_(size), spriteId_(spriteId) { }

private:
    Vector size_;
    int health_;
    bool is_charging_;
    int charge_;
    int spriteId_;
};

/*
class SpecialUnit : public Unit {
protected:
    SpecialUnit(int width) : Unit(width, 2) { };
};

// ---------------------------------------------------------------------- //
class CoreUnit : public Unit {
protected:
    CoreUnit() : Unit(1, 1) { };
};

class EliteUnit : public SpecialUnit {
protected:
    EliteUnit() : SpecialUnit(1) { };
};

class ChampionUnit : public SpecialUnit {
protected:
    ChampionUnit() : SpecialUnit(2) { };
};

// ---------------------------------------------------------------------- //

class Wall : public Unit {
public:
    virtual void onCreation() { };
    virtual void onDestroy() { };
    virtual void onCombination() { };

protected:
    Wall(Sprite weakWalls, Sprite strongWalls, int maxHealth) : Unit(1, 1), weakWalls_(weakWalls), strongWalls_(strongWalls), maxHealth_(maxHealth) { }

private:
    Sprite weakWalls_;
    Sprite strongWalls_;
    int maxHealth_;
};
*/