#pragma once
#include "units.hpp"
#include "army.hpp"

class Character {
    class CharacterAbility {
    public:
        CharacterAbility(Sprite notCharged, Sprite fullyCharged) : notCharged_(notCharged), fullyCharged_(fullyCharged), currentCharge_(100) { }

        virtual void use();
        virtual void addCharge(int addedCharge);
        virtual void subtractCharge(int subtractedCharge);

    private:
        Sprite notCharged_;
        Sprite fullyCharged_;
        int currentCharge_; // percentage
    };

public:
    static Character* fromFaction(Faction faction);

    int maxHealth() const { return maxHealth_; }

    /**
     *  Instanciate a random unit from the character's army
     */
    virtual Unit* randomUnitFactory(Player* player) const = 0;

    const void* spriteTiles;
    const size_t spriteTilesLen;
    const void* spritePal;
    const size_t spritePalLen;
    const void* bgBmp;
    const size_t bgBmpLen;
    const void* bgPal;
    const size_t bgPalLen;
protected:
    Character(
        const void* spriteTiles, size_t spriteTilesLen,
        const void* spritePal, size_t spritePalLen,
        const void* bgBmp, size_t bgBmpLen,
        const void* bgPal, size_t bgPalLen,
        int maxHealth,
        int maxUnits
    );

    //CharacterAbility ability_;
    int maxHealth_;
    int maxUnits_;
};