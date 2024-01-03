#include "game.hpp"
#include "units/units.hpp"
#include "character.hpp"

#include <array>

struct Army
{
    /* TODO CoreUnit soldierA;
    CoreUnit soldierB;
    CoreUnit soldierC;
    SpecialUnit specialA;
    SpecialUnit specialB; */
};

typedef std::array<Unit*, 48> BattleField; // 8 columns of 6-tile units

class Player
{
public:
    Player();
    ~Player();

    virtual void update();

    Unit*& at(int x, int y);

private:
    Character character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;

    bool me_; // false if it's the opponent
};
