#pragma once
enum Faction : unsigned int {
    Haven,
    Sylvan,
};

enum UnitType {
    None,

    Haven_Start,
    // Haven
    Swordsman,
    Archer,
    Spearman,

    // Haven special
    Knight,
    Angel,
    Haven_Wall,
    Haven_End,
};

struct Army
{
    UnitType soldierA;
    UnitType soldierB;
    UnitType soldierC;
    UnitType specialA;
    UnitType specialB;
};