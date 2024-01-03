#pragma once
#include "game.hpp"
#include "units/units.hpp"

class Character {
    class CharacterAbility {
    public:
        CharacterAbility(Sprite notCharged, Sprite fullyCharged) : notCharged_(notCharged), fullyCharged_(fullyCharged), currentCharge_(100) { };

        virtual void use();
        virtual void addCharge(int addedCharge);
        virtual void subtractCharge(int subtractedCharge);

    private:
        Sprite notCharged_;
        Sprite fullyCharged_;
        int currentCharge_; // percentage
    };

protected:
    //TODO Character() { }
private:
    Sprite characterSprite_;
    Sprite damagedCharacterSprite_;
    CharacterAbility ability_;
    //TODO Faction faction_;
    int maxHealth_;
    int maxUnits_;
};