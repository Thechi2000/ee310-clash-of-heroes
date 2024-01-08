#pragma once
#include "game.hpp"
#include "character.hpp"
#include "army.hpp"
#include "units.hpp"
#include <vector>

// 8 columns of 6-tile units
typedef std::array<Unit*, 48> BattleField;

class Player {
public:
    Player(Faction faction, bool sub);
    ~Player();

    void update();

    /**
     * Draw the player's state onto his screen
    */
    void render();
    bool handleInputs(); // Returns whether the turn is completed

    BattleField& getAllyBattlefield() { return battleField_; }
    BattleField& getEnnemyBattlefield() { return opponent_->getAllyBattlefield(); }
    const Army getArmy() { return army_; }
    Player* getEnnemy() { return opponent_; }

    /**
     * Process the removal of a unit at the given position
    */
    void handleDisparition(int battlefieldPosition);
    void updateBattleField();

    /**
     * Puts a unit at the given location.
     * Returns whether the operation was successfull
    */
    bool putUnit(Unit* unit, const Vector& position);

    /**
     * Handle the number action per turn
    */
   void startTurn() { remainingMoves_ = 3; };
   bool actionDone() { --remainingMoves_; return remainingMoves_ <= 0; }

    /**
     * Returns a reference for the Unit at the given position
    */
    Unit*& at(int x, int y);

    /**
     * Initialize the player's peripherals
    */
    void init();

private:
    /**
     * Returns the OamState to be used for this player (either &oamMain or &oamSub)
    */
    OamState* oam() const;
    bool hasSelectedUnit() const;
    void startCoreUnitCharge(int battlefieldPosition);

    /**
     * Compute the coordinates in pixel where a sprite should be displayed.
     * May add an 5 pixels vertical offset based on the selectedOffset parameter.
    */
    Vector computeOnScreenCoordinates(const Vector& coord, bool selectedOffset);

    Character* character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;
    int remainingMoves_;

    Vector selectedUnit_;
    uint32_t keyAPressedAt_;
    uint32_t touchScreenPressedAt_;

    std::vector<u16*> spritesGfx_;

    bool sub_; // false if it's the opponent
    Player* opponent_;

    PrintConsole console_;
};
