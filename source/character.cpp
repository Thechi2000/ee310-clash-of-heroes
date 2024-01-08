#include "character.hpp"
#include "sylvanBg.h"
#include "sylvanUnits.h"

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
        default:
            return nullptr;
    }
}
