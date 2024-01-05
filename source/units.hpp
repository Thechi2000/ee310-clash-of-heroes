#pragma once
#include "game.hpp"
#include <array>

struct Faction;
class Unit;
typedef std::array<Unit *, 48> BattleField; // 8 columns of 6-tile units

// ---------------------------------------------------------------------- //

class Unit
{
public:
    virtual int disappear(); // return damage dealt
    virtual void onTransformToWall(){};
    virtual void onTransformToAttack();
    const Vector &getSize() const { return size_; }

    virtual ~Unit() {}

    /* Returns true if the unit attacks */
    virtual bool updateCharge();
    /* Returns the damage dealt to the ennemi player*/

    virtual int attack(BattleField &opponentBattlefield, int attackedColumn);

    int getSpriteIdAt(const Vector &position)
    {
        if (!IN_RANGE(position.x, 0, size_.x - 1) || !IN_RANGE(position.y, 0, size_.y - 1))
        {
            return -1;
        }
        else
        {
            return spriteId_ + position.x * size_.y + position.y;
        }
    }

protected:
    Unit(int width, int length, int charge, int power, int toughness, int spriteId) : Unit({.x = width, .y = length}, charge, power, toughness, spriteId) {}
    Unit(Vector size, int charge, int power, int toughness, int spriteId) : size_(size), charge_(charge), power_(power), toughness_(toughness), health_(toughness), spriteId_(spriteId) {}

    Vector size_;

    bool is_charging_ = false;

    int toughness_;    // Base health and attack
    int power_;        // Max attack
    int charge_;       // #Turns before attacking
    int powerPerTurn_; // Power gained every charge turn
    // TODO Faction faction_;
    Sprite neutralSprites_;

    float health_;                 // Health and initial attack value
    int remainingChargeTurns_ = 0; // Remaining #turns before attacking

    int spriteId_;
};

class SpecialUnit : public Unit
{
protected:
    SpecialUnit(int width, int charge, int power, int toughness, int spriteId) : Unit(width, 2, charge, power, toughness, spriteId){};
};

// ---------------------------------------------------------------------- //

class CoreUnit : public Unit
{
protected:
    CoreUnit(int charge, int power, int toughness, int spriteId) : Unit(1, 1, charge, power, toughness, spriteId){};
};

class EliteUnit : public SpecialUnit
{
protected:
    EliteUnit(int charge, int power, int toughness, int spriteId) : SpecialUnit(1, charge, power, toughness, spriteId){};
};

class ChampionUnit : public SpecialUnit
{
protected:
    ChampionUnit(int charge, int power, int toughness, int spriteId) : SpecialUnit(2, charge, power, toughness, spriteId){};
};

// ---------------------------------------------------------------------- //

class Wall : public Unit
{
public:
    virtual void onCreation(){};
    virtual void onDestroy(){};
    virtual void onCombination(){};

protected:
    /* Power : Max health / Toughness : Initial health */
    Wall(Sprite weakWalls, Sprite strongWalls, int maxHealth, int spriteId) : Unit(1, 1, 0, 16, 8, spriteId), weakWalls_(weakWalls), strongWalls_(strongWalls) {}

private:
    Sprite weakWalls_;
    Sprite strongWalls_;
};