#pragma once
#include "game.hpp"
#include "army.hpp"
#include <array>

class Unit;
class Player;
typedef std::array<Unit*, 48> BattleField;

// ---------------------------------------------------------------------- //

class Unit {
public:
    virtual int disappear(); // return damage dealt
    virtual void onTransformToWall() { }
    virtual void onTransformToAttack();
    const Vector& getSize() const { return size_; }
    virtual bool getIsCharging() const { return isCharging_; }
    virtual int getToughness() const { return toughness_; }
    virtual int getPower() const { return power_; }
    virtual int getCharge() const { return charge_; }
    const UnitType getType() const { return unitType_; }
    const ColorType getColor() const { return colorType_; }

    virtual void heal();
    virtual void onFusion(Unit* fusionUnit);
    const bool isEqual(Unit* other) { return other == nullptr ? false : (colorType_ == other->getColor()) && (unitType_ == other->getType()) && (isCharging_ == other->getIsCharging()); }

    virtual ~Unit() { }

    /* Returns true if the unit attacks */
    virtual bool updateCharge();
    /* Returns the damage dealt to the ennemi player*/

    virtual int attack(BattleField& opponentBattlefield, int attackedColumn);

    int getSpriteIdAt(const Vector& position) {
        if (!IN_RANGE(position.x, 0, size_.x - 1) || !IN_RANGE(position.y, 0, size_.y - 1)) {
            return -1;
        } else {
            return spriteId_ + static_cast<int>(colorType_) * size_.x * size_.y + position.x * size_.y + position.y;
        }
    }

protected:
    Unit(int width, int length, int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) :
        Unit({ .x = width, .y = length },
            charge,
            power,
            toughness,
            currentPlayer,
            unitType,
            colorType,
            spriteId) { }
    Unit(Vector size, int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) :
        size_(size),
        charge_(charge),
        power_(power),
        toughness_(toughness),
        health_(toughness),
        currentPlayer_(currentPlayer),
        unitType_(unitType),
        colorType_(colorType),
        spriteId_(spriteId) { }

    Vector size_;

    bool isCharging_ = false;

    int toughness_;    // Base health and attack
    int power_;        // Max attack
    int charge_;       // #Turns before attacking
    Sprite neutralSprites_;

    int fusion_;

    float health_;                 // Health and initial attack value
    int remainingChargeTurns_ = 0; // Remaining #turns before attacking

    int spriteId_;

    Player* currentPlayer_;
    UnitType unitType_;
    ColorType colorType_;
};

class SpecialUnit : public Unit {
protected:
    SpecialUnit(int width, int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) : Unit(width, 2, charge, power, toughness, currentPlayer, unitType, colorType, spriteId) { };
};

// ---------------------------------------------------------------------- //

class CoreUnit : public Unit {
protected:
    CoreUnit(int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) : Unit(1, 1, charge, power, toughness, currentPlayer, unitType, colorType, spriteId) { };
};

class EliteUnit : public SpecialUnit {
protected:
    EliteUnit(int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) : SpecialUnit(1, charge, power, toughness, currentPlayer, unitType, colorType, spriteId) { };
};

class ChampionUnit : public SpecialUnit {
public:
    virtual int attack(BattleField& opponentBattlefield, int attackedColumn);

protected:
    ChampionUnit(int charge, int power, int toughness, Player* currentPlayer, UnitType unitType, ColorType colorType, int spriteId) : SpecialUnit(2, charge, power, toughness, currentPlayer, unitType, colorType, spriteId) { };
};

// ---------------------------------------------------------------------- //

class Wall : public Unit {
public:
    virtual void onCreation() { };
    virtual void onDestroy() { };
    virtual void onCombination() { };

protected:
    /* Power : Max health / Toughness : Initial health */
    Wall(int health, Player* currentPlayer, UnitType unitType, int spriteId) : Unit(1, 1, 0, health * 2, health, currentPlayer, unitType, WallColor, spriteId) { }
};