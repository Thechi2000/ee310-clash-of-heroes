#pragma once
enum Faction : unsigned int {
    Haven,
    Sylvan,
};

enum UnitType {
    None,

    Haven_Start,
    // Haven
    Soldier,
    Archer,
    Spearman,

    // Haven special
    Knight,
    Angel,
    Haven_End,

    SubUnits,
    // Position (B : Back - F : Front - R : Right - L : Left)
    CoreCharging_F,
    CoreCharging_B,
    CoreCharging_BB,
    Elite_B,
    Champion_LB,
    Champion_RF,
    Champion_RB,
};

struct Army
{
    UnitType soldierA;
    UnitType soldierB;
    UnitType soldierC;
    UnitType specialA;
    UnitType specialB;
};