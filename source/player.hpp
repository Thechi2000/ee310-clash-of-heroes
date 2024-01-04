#include "game.hpp"
#include "units/units.hpp"
#include "character.hpp"

#include <array>
#include <vector>

struct Army {
    /* TODO CoreUnit soldierA;
    CoreUnit soldierB;
    CoreUnit soldierC;
    SpecialUnit specialA;
    SpecialUnit specialB; */
};

typedef std::array<Unit*, 48> BattleField; // 8 columns of 6-tile units

class Player {
public:
    Player();
    ~Player();

    virtual void update();

    void render();

    Unit*& at(int x, int y);

private:
    OamState* oam() const;
    const void* tiles() const;
    size_t tilesLen() const;
    const void* pal() const;
    size_t palLen() const;

    Character character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;

    std::vector<u16*> spritesGfx_;

    bool me_; // false if it's the opponent
};
