#include "game.hpp"
#include "units/units.hpp"
#include "character.hpp"

struct Army {
    CoreUnit soldierA;
    CoreUnit soldierB;
    CoreUnit soldierC;
    SpecialUnit specialA;
    SpecialUnit specialB;
};

typedef Unit BattleField[8][6]; // 8 columns of 6-tile units

class Player : public Renderable, public InputHandler {
public:
    virtual void update();
private:
    Character character_;
    Army army_;
    BattleField battleField_;

    int currentHealth_;
    int invocableUnits_;

    bool me_; // false if it's the opponent
};

