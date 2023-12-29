#include "menu.hpp"
#include "abilities_menu_background.h"
#include "portraits.h"

struct CharacterDisplay {
    Sprite sprite;
    const char* name;
    const char* spell_name;
    const char* spell_description;
    const char* spell_sprite;
    const char* wall_name;
    const char* wall_description;
    const char* wall_sprite;
    int x, y;
};

const CharacterDisplay characters[] = { CharacterDisplay {
        .name = "test1",
        .spell_name = "SPELL1",
        .spell_description = "spell test test test",
        .wall_name = "WALL",
        .wall_description = "wall test test test",
        .x = 0,
        .y = 0,
    },
    CharacterDisplay {
        .name = "test2",
        .spell_name = "SPELL2",
        .spell_description = "spell test test test",
        .wall_name = "WALL",
        .wall_description = "wall test test test",
        .x = 0,
        .y = 0,
    },
    CharacterDisplay {
        .name = "test3",
        .spell_name = "SPELL3",
        .spell_description = "spell test test test",
        .wall_name = "WALL",
        .wall_description = "wall test test test",
        .x = 0,
        .y = 0,
    },
    CharacterDisplay {
        .name = "test4",
        .spell_name = "SPELL4",
        .spell_description = "spell test test test",
        .wall_name = "WALL",
        .wall_description = "wall test test test",
        .x = 0,
        .y = 0,
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
                BG_MAP_RAM_SUB(24)[(j + y) * 32 + (i + x)] = portraitsMap[j * 64 + (i + (16 * id))];
            }
        }
    }
}

CharacterSelectionMenu::CharacterSelectionMenu() : selected_character(0), displayed_character(-1) {
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_3_2D | DISPLAY_BG3_ACTIVE;
    BGCTRL[3] = BG_BMP_BASE(1) | BG_BMP8_256x256;
    consoleInit(&main_printer, 2, BgType_Text4bpp, BgSize_T_256x256, 4, 0, true, true);

    for (int i = 0; i < abilities_menu_backgroundBitmapLen; ++i) {
        BG_BMP_RAM(1)[i] = ((u16*)abilities_menu_backgroundBitmap)[i] | 0x1010;

        //iprintf("%d, %d\n", ((u16*)abilities_menu_backgroundBitmap)[i] | 0x1010);
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
    REG_DISPCNT_SUB = MODE_1_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
    BGCTRL_SUB[2] = BG_TILE_BASE(4) | BG_MAP_BASE(24) | BG_32x32 | BG_COLOR_256;
    BGCTRL_SUB[3] = BG_BMP_BASE(8) | BG_BMP8_256x256;
    consoleInit(&sub_printer, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

    memcpy(BG_PALETTE_SUB + 16, portraitsPal, portraitsPalLen);
    memcpy(BG_TILE_RAM_SUB(4), portraitsTiles, portraitsTilesLen);
}

void CharacterSelectionMenu::render() {
    if (displayed_character != selected_character) {
        auto character = &characters[selected_character];

        consoleSelect(&main_printer);

        main_printer.cursorX = 2;
        main_printer.cursorY = 2;
        printf(
            "\x1B[32m\033[3;4H%s\033[5;3H%s\033[14;4H%s\033[16;3H%s",
            character->spell_name,
            character->spell_description,
            character->wall_name,
            character->wall_description
        );

        drawCharacter(CLAMP_CHARACTER_ID(selected_character - 1), -2, 5);
        drawCharacter(CLAMP_CHARACTER_ID(selected_character + 1), 22, 5);
        drawCharacter(selected_character, 8, 2);

        consoleSelect(&sub_printer);
        printf("\x1B[32m\033[19;12H%s", character->name);

        displayed_character = selected_character;
    }
}

void CharacterSelectionMenu::handle_inputs() {
    int keys = keysDown();

    if (keys & KEY_RIGHT) {
        selected_character++;
    } else if (keys & KEY_LEFT) {
        selected_character--;
    } else if (keys & KEY_A) {
        confirmSelection();
    }

    if (keys & KEY_TOUCH) {
        touchPosition pos = touchReadXY();
        int x = pos.px, y = pos.py;

        if (IN_RANGE(x, 64, 191) && IN_RANGE(y, 16, 143)) {
            confirmSelection();
        } else if (IN_RANGE(y, 80, 207)) {
            if (IN_RANGE(x, 0, 111)) {
                selected_character--;
            } else if (IN_RANGE(x, 176, 255)) {
                selected_character++;
            }
        }
    }

    selected_character = CLAMP_CHARACTER_ID(selected_character);
}

void CharacterSelectionMenu::confirmSelection() {
    TO_BE_IMPLEMENTED();
}
