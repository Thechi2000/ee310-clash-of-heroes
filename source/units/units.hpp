#include "game.hpp"

struct Sprite;
struct Faction;

struct Pair {
    int x;
    int y;
} typedef;

// ---------------------------------------------------------------------- // 

class Unit : public Renderable {
public:
    void update();
    int disappear(); // return damage dealt
    void transformToWall();
    void transformToAtack();
    Pair getSize();
    Pair getPosition();

protected:
    Unit(int width, int length) : width_(width), length_(length) {};
    Unit(Pair size) : width_(size.x), length_(size.y) {};

private :
    int width_; // horizontal
    int length_; // vertical

    int xPos; // horizontal, from left to right
    int yPos; // vertical, from first row to last one

    int health;

    Faction faction_;

    Sprite neutralSprites_;
};

class SpecialUnit : public Unit {
protected:
    SpecialUnit(int width) : Unit(width, 2) {};
};

// ---------------------------------------------------------------------- // 

class CoreUnit : public Unit {
protected:
    CoreUnit() : Unit(1, 1) {}; 
};

class EliteUnit : public SpecialUnit {
protected:
    EliteUnit() : SpecialUnit(1) {};
};

class ChampionUnit : public SpecialUnit {
protected:
    ChampionUnit() : SpecialUnit(2) {};
};

// ---------------------------------------------------------------------- // 

class ChargingUnit : public Unit {
public:
    static void startCharge(Unit unit);
    virtual void attack();
protected:
    ChargingUnit(Unit initialUnit) : Unit(initialUnit.getSize()), isCharging_(true) {};
private:
    bool isCharging_ = false;

    int power;

    int currentCharge_;
    Sprite chargingSprites_;
    Sprite attackingSprites_;
};

// ---------------------------------------------------------------------- // 

class WallType : public Renderable {
public:
    WallType(Sprite weakWalls, Sprite strongWalls, int maxHealth) : weakWalls_(weakWalls), strongWalls_(strongWalls), maxHealth_(maxHealth) {};

    virtual void onCreation() {};
    virtual void onDestroy() {};
    virtual void onCombination() {};

private:
    Sprite weakWalls_;
    Sprite strongWalls_;
    int maxHealth_;
};

class Wall : public Unit {
protected:
    Wall() : Unit(1, 1) {};

private:
    WallType wallType_;
};