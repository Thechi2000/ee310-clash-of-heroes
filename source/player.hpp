#pragma once
#include "game.hpp"
#include "character.hpp"
#include "army.hpp"
#include "units.hpp"
#include <vector>

struct BattleField;
class Unit;

class Player {
public:
    Player(Faction faction);
    ~Player();

    virtual void update();

    void render();
    void handleInputs();

    BattleField* getAllyBattlefield() { return battleField_; }
    BattleField* getEnnemyBattlefield() { return opponent_->getAllyBattlefield(); }

    Unit*& at(int x, int y);

    void init();

private:
    OamState* oam() const;
    bool hasSelectedUnit() const;

    Character* character_;
    Army army_;
    BattleField* battleField_;

    int currentHealth_;
    int invocableUnits_;

    Vector selectedUnit_;
    uint32_t keyAPressedAt_;
    uint32_t touchScreenPressedAt_;

    std::vector<u16*> spritesGfx_;

    bool me_; // false if it's the opponent
    Player* opponent_;

    PrintConsole console_;
};
