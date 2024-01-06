#pragma once

enum Faction {
    Haven,
};

enum CoreUnitType {
    // Haven
    Soldier,
    Archer,
    Spearman,

};

enum SpecialUnitType {
    //Haven
    Knight,
    Angel,
    
};

struct Army
{
    CoreUnitType soldierA;
    CoreUnitType soldierB;
    CoreUnitType soldierC;
    SpecialUnitType specialA;
    SpecialUnitType specialB;
};