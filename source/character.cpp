#include "character.hpp"
#include "sylvanBg.h"
#include "sylvanUnits.h"
#include "havenBg.h"
#include "havenUnits.h"

#include "haven.hpp"

class SylvanCharacter : public Character {
public:
    SylvanCharacter() : Character(
        sylvanUnitsTiles, sylvanUnitsTilesLen,
        sylvanUnitsPal, sylvanUnitsPalLen,
        sylvanBgBitmap, sylvanBgBitmapLen,
        sylvanBgPal, sylvanBgPalLen,
        100,
        20
    ) { }

    virtual Unit* randomUnitFactory(Player* player) const {
        return nullptr;
    }
};

class HavenCharacter : public Character {
public:
    HavenCharacter() : Character(
        havenUnitsTiles, havenUnitsTilesLen,
        havenUnitsPal, havenUnitsPalLen,
        havenBgBitmap, havenBgBitmapLen,
        havenBgPal, havenBgPalLen,
        100,
        20
    ) { }

    virtual Unit* randomUnitFactory(Player* player) const {
        int r = rand() % 12;

        if (IN_RANGE(r, 0, 3)) {
            return new haven::Swordsman(player, ColorType::ColorA);
        } else if (IN_RANGE(r, 3, 6)) {
            return new haven::Spearman(player, ColorType::ColorB);
        } else if (IN_RANGE(r, 6, 9)) {
            return new haven::Archer(player, ColorType::ColorC);
        } else if (IN_RANGE(r, 9, 11)) {
            return new haven::Knight(player, static_cast<ColorType>(rand() % 3));
        } else {
            return new haven::Angel(player, static_cast<ColorType>(rand() % 3));
        }
    }
};

Character::Character(
    const void* spriteTiles, size_t spriteTilesLen,
    const void* spritePal, size_t spritePalLen,
    const void* bgBmp, size_t bgBmpLen,
    const void* bgPal, size_t bgPalLen,
    int maxHealth,
    int maxUnits
) :
    spriteTiles(spriteTiles), spriteTilesLen(spriteTilesLen),
    spritePal(spritePal), spritePalLen(spritePalLen),
    bgBmp(bgBmp), bgBmpLen(bgBmpLen),
    bgPal(bgPal), bgPalLen(bgPalLen),
    maxHealth_(maxHealth),
    maxUnits_(maxUnits) { }

Character* Character::fromFaction(Faction faction) {
    switch (faction) {
        case Faction::Sylvan:
            return new SylvanCharacter();
        case Faction::Haven:
            return new HavenCharacter();
        default:
            return nullptr;
    }
}
