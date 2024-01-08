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
    /**
     * Handle the inputs for this player and return whether the turn is completed
    */
    bool handleInputs();

    /**
     * Put a unit at the given location.
     * Returns whether the operation was successfull
    */
    bool putUnit(Unit* unit, const Vector& position);


    /**
     * Return a reference for the Unit at the given position
    */
    Unit*& at(int x, int y);

    /**
     * Initialize the player's peripherals
    */
    void init();

private:
    /**
     * Return the OamState to be used for this player (either &oamMain or &oamSub)
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
    BattleField battleField_;

    int currentHealth_;

    Vector selectedUnit_;
    uint32_t keyAPressedAt_;
    uint32_t touchScreenPressedAt_;

    std::vector<u16*> spritesGfx_;

    bool sub_;

    PrintConsole console_;
};
