#pragma once
#include "game.hpp"
#include "character.hpp"
#include "army.hpp"
#include "units.hpp"
#include <vector>

// 8 columns of 6-tile units
typedef std::array<Unit *, 48> BattleField;
class Unit;

class Player
{
public:
    Player(Faction faction, bool sub);
    ~Player();

    virtual void update();

    void render();
    bool handleInputs(); // Returns whether the turn is completed

    BattleField &getAllyBattlefield() { return battleField_; }
    BattleField &getEnnemyBattlefield() { return opponent_->getAllyBattlefield(); }
    const Army getArmy() { return army_; }
    Player* getEnnemy() { return opponent_; }

    void handleDisparition(int battlefieldPosition);
    void updateBattleField();

    Unit *&at(int x, int y);

    void init();

private:
    OamState *oam() const;
    bool hasSelectedUnit() const;
    void startCoreUnitCharge(int battlefieldPosition);

    Character *character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;

    Vector selectedUnit_;
    uint32_t keyAPressedAt_;
    uint32_t touchScreenPressedAt_;

    std::vector<u16 *> spritesGfx_;

    bool sub_; // false if it's the opponent
    Player* opponent_;

    PrintConsole console_;
};
