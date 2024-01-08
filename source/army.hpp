#pragma once

enum ColorType {
    ColorA,
    ColorB,
    ColorC,
    WallColor,
};

enum Faction : unsigned int {
    Haven,
    Sylvan,
};

enum UnitType {
    None = 0,

    // Haven
    Swordsman,
    HavenArcher,
    Spearman,

    // Haven special
    Knight,
    Angel,
    HavenWall,

    // Sylvan
    Bear,
    SylvanArcher,
    Nymph,

    // Sylvan special
    Deer,
    Drake,
    SylvanWall,
};

struct Army {
    UnitType soldierA;
    UnitType soldierB;
    UnitType soldierC;
    UnitType specialA;
    UnitType specialB;
    UnitType wall;
};