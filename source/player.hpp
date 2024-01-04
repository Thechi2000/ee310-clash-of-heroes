#include "game.hpp"
#include "character.hpp"
#include "units/army.hpp"
#include "units/units.hpp"

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
