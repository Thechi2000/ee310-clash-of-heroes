#pragma once

/**
 * Color of a unit. Units a same color can be aligned to create walls or charge units
*/
enum ColorType {
    ColorA,
    ColorB,
    ColorC,
    WallColor,
};

/**
 * Factions implemented in the game
*/
enum Faction : unsigned int {
    Haven,
    Sylvan,
};

/**
 * All units from the game
*/
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

/**
 * Army of a player. Each army contains 1 wall type, 3 core units and 2 special units
*/
struct Army {
    UnitType soldierA;
    UnitType soldierB;
    UnitType soldierC;
    UnitType specialA;
    UnitType specialB;
    UnitType wall;
};