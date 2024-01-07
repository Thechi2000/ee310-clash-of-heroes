#pragma once

enum Faction {
    Haven,
    Sylvan,
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