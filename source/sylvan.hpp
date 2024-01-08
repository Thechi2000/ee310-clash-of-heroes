#include "units.hpp"

namespace sylvan {
class Bear : public CoreUnit {
public:
    Bear(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 11, 3, currentPlayer, UnitType::Bear, colorType, 3) { };
};

class Archer : public CoreUnit {
public:
    Archer(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 11, 3, currentPlayer, UnitType::SylvanArcher, colorType, 6) { };
};

class Nymph : public CoreUnit {
public:
    Nymph(Player* currentPlayer, ColorType colorType) : CoreUnit(3, 11, 3, currentPlayer, UnitType::Nymph, colorType, 9) { };
};

class Deer : public EliteUnit {
public:
    Deer(Player* currentPlayer, ColorType colorType) : EliteUnit(4, 30, 6, currentPlayer, UnitType::Deer, colorType, 12) { }
};

class Drake : public ChampionUnit {
public:
    Drake(Player* currentPlayer, ColorType colorType) : ChampionUnit(4, 30, 6, currentPlayer, UnitType::Drake, colorType, 42) { }
};

class SylvanWall : public Wall {
public:
    SylvanWall(Player* currentPlayer) : Wall(8, currentPlayer, UnitType::SylvanWall, 1) { };
};
}