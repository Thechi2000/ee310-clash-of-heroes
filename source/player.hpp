#include "game.hpp"
#include "character.hpp"
#include "army.hpp"
#include "units.hpp"
#include <vector>

class Player {
public:
    Player();
    ~Player();

    virtual void update();

    void render();
    void handleInputs();

    Unit*& at(int x, int y);

private:
    OamState* oam() const;
    const void* tiles() const;
    size_t tilesLen() const;
    const void* pal() const;
    size_t palLen() const;

    bool hasSelectedUnit() const;

    Character character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;

    Vector selectedUnit_;
    uint32_t keyAPressedAt_;
    uint32_t touchScreenPressedAt_;

    std::vector<u16*> spritesGfx_;

    bool me_; // false if it's the opponent

    PrintConsole console_;
};
