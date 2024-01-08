#include "menu.hpp"
#include "abilities_menu_background.h"
#include "portraits.h"
#include "portraitsBackground.h"
#include "gameBattle.hpp"
#include <maxmod9.h>
#include "soundbank.h"

struct CharacterDisplay {
    const char* name;
    const char* spell_name;
    const char* spell_description;
    const char* spell_sprite;
    const char* wall_name;
    const char* wall_description;
    const char* wall_sprite;
    int x, y;
    Faction faction;
};

const CharacterDisplay characters[] = { CharacterDisplay {
        .name = "Anwen",
        .spell_name = "ANWNEN'S ARROW",
        .spell_description = "Anwen's arrow",
        .wall_name = "SYLVAN WALL",
        .wall_description = "Build a mystical wood wall",
        .x = 0,
        .y = 0,
        .faction = Faction::Sylvan,
    },
    CharacterDisplay {
        .name = "Findan",
        .spell_name = "FINDAN'S DISCRETION",
        .spell_description = "Findan's discretion",
        .wall_name = "SYLVAN WALL",
        .wall_description = "Build a mystical wood wall",
        .x = 0,
        .y = 0,
        .faction = Faction::Sylvan,
    },
    CharacterDisplay {
        .name = "Godric",
        .spell_name = "GODRIC'S GRACE",
        .spell_description = "Gordric's grace",
        .wall_name = "HAVEN WALL",
        .wall_description = "Build a wall of light",
        .x = 0,
        .y = 0,
        .faction = Faction::Haven,
    },
    CharacterDisplay {
        .name = "Varkas",
        .spell_name = "VARKAS' ARMOR",
        .spell_description = "Varkas' armor",
        .wall_name = "HAVEN WALL",
        .wall_description = "Build a wall of light",
        .x = 0,
        .y = 0,
        .faction = Faction::Haven,
    }
};
const size_t character_count = sizeof(characters) / sizeof(CharacterDisplay);
const size_t spritesheet_width = 720;

#define CLAMP_CHARACTER_ID(id) (((id) + character_count) % character_count)

void drawCharacter(int id, int x, int y) {
    assert(0 <= id && id < character_count);

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (IN_RANGE(i + x, 0, 31) && IN_RANGE(j + y, 0, 23)) {
                BG_MAP_RAM_SUB(16)[(j + y) * 32 + (i + x)] = portraitsMap[j * 64 + (i + (16 * id))];
            }
        }
    }
}

CharacterSelectionMenu::CharacterSelectionMenu() : selectedCharacter_(0), displayedCharacter_(-1) { }
CharacterSelectionMenu::~CharacterSelectionMenu() { }

void CharacterSelectionMenu::init() {
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_3_2D | DISPLAY_BG3_ACTIVE;
    BGCTRL[3] = BG_BMP_BASE(1) | BG_BMP8_256x256;
    consoleInit(&mainPrinter_, 2, BgType_Text4bpp, BgSize_T_256x256, 4, 0, true, true);

    for (int i = 0; i < abilities_menu_backgroundBitmapLen; ++i) {
        BG_BMP_RAM(1)[i] = ((u16*)abilities_menu_backgroundBitmap)[i] | 0x1010;
    }
    for (int i = 0; i < abilities_menu_backgroundSharedPalLen / 2; ++i) {
        BG_PALETTE[i + 16] = abilities_menu_backgroundSharedPal[i];
    }

    bgTransform[3]->hdx = 1 * 256;
    bgTransform[3]->vdx = 0 * 256;
    bgTransform[3]->hdy = 0 * 256;
    bgTransform[3]->vdy = 1 * 256;
    bgTransform[3]->dx = 0 * 256;
    bgTransform[3]->dy = 0 * 256;

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
    consoleInit(&subPrinter_, 1, BgType_Text4bpp, BgSize_T_256x256, 8, 0, false, true);
    BGCTRL_SUB[2] = BG_TILE_BASE(4) | BG_MAP_BASE(16) | BG_32x32 | BG_COLOR_256;
    BGCTRL_SUB[3] = BG_TILE_BASE(8) | BG_MAP_BASE(24) | BG_32x32 | BG_COLOR_256;

    dmaCopy(portraitsBackgroundTiles, BG_TILE_RAM_SUB(8), portraitsBackgroundTilesLen);
    dmaCopy(portraitsBackgroundSharedPal, BG_PALETTE_SUB, portraitsBackgroundSharedPalLen);
    dmaCopy(portraitsBackgroundMap, BG_MAP_RAM_SUB(24), portraitsBackgroundMapLen);

    dmaCopy(portraitsTiles, BG_TILE_RAM_SUB(4), portraitsTilesLen);
    dmaCopy(portraitsPal, BG_PALETTE_SUB + 4, portraitsPalLen);

    mmLoad(MOD_MENU);
    mmLoadEffect(SFX_MENU_SELECT);
    mmLoadEffect(SFX_MENU_SWAP);

    mmStart(MOD_MENU, MM_PLAY_LOOP);
    mmSetModuleVolume(256);
}
void CharacterSelectionMenu::deinit() {
    mmUnload(MOD_MENU);
    mmUnloadEffect(SFX_MENU_SELECT);
    mmUnloadEffect(SFX_MENU_SWAP);
}

void CharacterSelectionMenu::render() {
    if (displayedCharacter_ != selectedCharacter_) {
        auto character = &characters[selectedCharacter_];

        drawCharacter(CLAMP_CHARACTER_ID(selectedCharacter_ - 1), -2, 5);
        drawCharacter(CLAMP_CHARACTER_ID(selectedCharacter_ + 1), 22, 5);
        drawCharacter(selectedCharacter_, 8, 2);

        consoleSelect(&mainPrinter_);
        consoleClear();

        printf(
            "\x1B[32m\033[3;4H%s\033[5;3H%s\033[14;4H%s\033[16;3H%s",
            character->spell_name,
            character->spell_description,
            character->wall_name,
            character->wall_description
        );

        consoleSelect(&subPrinter_);
        consoleClear();
        printf("\x1B[32m\033[19;12H%s", character->name);
        printf("\x1B[32m\033[0;12HPlayer %s", firstPlayerFaction_.has_value() ? "2" : "1");

        displayedCharacter_ = selectedCharacter_;
    }
}

GameState* CharacterSelectionMenu::handle_inputs() {
    int keys = keysDown();

    if (keys & KEY_RIGHT) {
        mmEffect(SFX_MENU_SWAP);
        selectedCharacter_++;
    } else if (keys & KEY_LEFT) {
        mmEffect(SFX_MENU_SWAP);
        selectedCharacter_--;
    } else if (keys & KEY_A) {
        mmEffect(SFX_MENU_SELECT);
        return confirmSelection();
    } else if (keys & KEY_B) {
        if (secondPlayerFaction_.has_value()) {
            secondPlayerFaction_ = {};
            displayedCharacter_ = -1;
            selectedCharacter_ = 0;
        } else if (firstPlayerFaction_.has_value()) {
            firstPlayerFaction_ = {};
            displayedCharacter_ = -1;
            selectedCharacter_ = 0;
        }
    }

    if (keys & KEY_TOUCH) {
        touchPosition pos = touchReadXY();
        int x = pos.px, y = pos.py;

        if (IN_RANGE(x, 64, 191) && IN_RANGE(y, 16, 143)) {
            return confirmSelection();
        } else if (IN_RANGE(y, 80, 207)) {
            if (IN_RANGE(x, 0, 111)) {
                selectedCharacter_--;
            } else if (IN_RANGE(x, 176, 255)) {
                selectedCharacter_++;
            }
        }
    }

    selectedCharacter_ = CLAMP_CHARACTER_ID(selectedCharacter_);

    return nullptr;
}

GameState* CharacterSelectionMenu::confirmSelection() {
    (firstPlayerFaction_.has_value() ? secondPlayerFaction_ : firstPlayerFaction_) = characters[selectedCharacter_].faction;

    displayedCharacter_ = -1;
    selectedCharacter_ = 0;

    return (firstPlayerFaction_.has_value() && secondPlayerFaction_.has_value()) ? new GameBattle(firstPlayerFaction_.value(), secondPlayerFaction_.value()) : nullptr;
}
