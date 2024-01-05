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
