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
