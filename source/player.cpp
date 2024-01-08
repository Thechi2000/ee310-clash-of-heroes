#include "player.hpp"

#define SPRITE_SIZE (32 * 32)

class TestUnit : public Unit {
public:
    virtual ~TestUnit() { }

    TestUnit(int x, int y, Player* player, int spriteId) : Unit(x, y, 3, 6, 4, player, spriteId) { }

    void onTransformToAttack() { }
    void onTransformToWall() { }
    bool updateCharge() { }
};

Player::Player(Faction faction, bool sub) :
    character_(Character::fromFaction(faction)),
    selectedUnit_{ -1, -1 },
    sub_(sub) {
    battleField_->units.fill(nullptr);

    for (int i = 0; i < 48; ++i) {
        if (rand() % 3 == 0) {
            battleField_->units[i] = new TestUnit(1, 1, this, i % 9 + 1);
        }
    }
    // END REMOVE
}

void Player::init() {
    consoleInit(&console_, 0, BgType_Text4bpp, BgSize_T_256x256, 8, 0, !sub_, true);

    if (sub_) {
        VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
        REG_DISPCNT_SUB = 0; // Disable the display to avoid clutter on the screen while loading the different assets
        BGCTRL_SUB[2] = BG_BMP_BASE(4) | BgSize_B8_256x256;

        mdCopy(BG_BMP_RAM_SUB(4), character_->bgBmp, character_->bgBmpLen, [](u8 a, size_t i, u8* array) {
            while (array[i] == 255) { i--; }
            return array[i];
            });
        dmaCopy(character_->bgPal, BG_PALETTE_SUB, character_->bgPalLen);
        BG_PALETTE_SUB[255] = ARGB16(1, 28, 60, 28);

        bgTransform[6]->hdx = -1 * 256;
        bgTransform[6]->vdx = 0 * 256;
        bgTransform[6]->hdy = 0 * 256;
        bgTransform[6]->vdy = -1 * 256;
        bgTransform[6]->dx = 255 * 256;
        bgTransform[6]->dy = 191 * 256;

        VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
        swiCopy(character_->spritePal, SPRITE_PALETTE_SUB, character_->spritePalLen / 2);
    } else {
        VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
        REG_DISPCNT = 0; // Disable the display to avoid clutter on the screen while loading the different assets
        BGCTRL[2] = BG_BMP_BASE(4) | BgSize_B8_256x256;

        mdCopy(BG_BMP_RAM(4), character_->bgBmp, character_->bgBmpLen, [](u8 a, size_t i, u8* array) {
            while (array[i] == 255) { i--; }
            return array[i];
            });
        dmaCopy(character_->bgPal, BG_PALETTE, character_->bgPalLen);
        BG_PALETTE[255] = ARGB16(1, 28, 60, 28);

        bgTransform[2]->hdx = 1 * 256;
        bgTransform[2]->vdx = 0 * 256;
        bgTransform[2]->hdy = 0 * 256;
        bgTransform[2]->vdy = 1 * 256;
        bgTransform[2]->dx = 0 * 256;
        bgTransform[2]->dy = 0 * 256;

        VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE;
        swiCopy(character_->spritePal, SPRITE_PALETTE, character_->spritePalLen / 2);
    }

    oamInit(oam(), SpriteMapping_1D_128, false);

    for (int i = 0; i < character_->spriteTilesLen / SPRITE_SIZE; ++i) {
        auto gfx = oamAllocateGfx(oam(), SpriteSize_32x32, SpriteColorFormat_256Color);
        spritesGfx_.push_back(gfx);
        swiCopy(character_->spriteTiles + i * SPRITE_SIZE, gfx, SPRITE_SIZE / 2);
    }
}

Player::~Player() {
    delete character_;

    for (size_t i = 0; i < battleField_->units.size(); ++i) {
        auto unit = battleField_->units[i];

        if (unit != nullptr) {
            for (size_t x = 0; x < unit->getSize().x; ++x) {
                for (size_t y = 0; y < unit->getSize().y; ++y) {
                    at(x, y) = nullptr;
                }
            }

            delete unit;
        }
    }

    for (auto gfx : spritesGfx_) {
        oamFreeGfx(oam(), gfx);
    }
}

Unit*& Player::at(int x, int y) {
    return battleField_->units[x + 8 * y];
}

OamState* Player::oam() const {
    return sub_ ? &oamSub : &oamMain;
}

bool Player::hasSelectedUnit() const { return selectedUnit_.x != -1 && selectedUnit_.y != -1; }

void Player::render() {
    for (size_t x = 0; x < 8; ++x) {
        for (size_t y = 0; y < 6; ++y) {
            auto unit = at(x, y);
            if (unit != nullptr) {
                Vector relativePosition{ .x = 0, .y = 0 };
                while (at(x - relativePosition.x, y) == unit) {
                    ++relativePosition.x;
                }
                relativePosition.x--;

                while (at(x - relativePosition.x, y - relativePosition.y) == unit) {
                    ++relativePosition.y;
                }
                relativePosition.y--;

                bool isSelected = selectedUnit_.x == x && selectedUnit_.y == y;

                auto spriteId = unit->getSpriteIdAt(relativePosition);
                oamSet(
                    oam(),
                    x + y * 8,
                    x * 28 + 16, y * 28 + (sub_ ? 0 : 20) + (isSelected ? 5 : 0),
                    0,
                    0,
                    SpriteSize_32x32,
                    SpriteColorFormat_256Color,
                    spritesGfx_[spriteId],
                    -1,
                    false,
                    false,
                    false, false,
                    false
                );
            } else {
                oamSetHidden(oam(), x + y * 8, true);
            }
        }
    }

    if (hasSelectedUnit() && at(selectedUnit_.x, selectedUnit_.y) == nullptr) {
        oamSet(
            oam(),
            49,
            selectedUnit_.x * 28 + 16, selectedUnit_.y * 28 + (sub_ ? 0 : 20),
            0,
            0,
            SpriteSize_32x32,
            SpriteColorFormat_256Color,
            spritesGfx_[0],
            -1,
            false,
            false,
            false, false,
            false
        );
    } else {
        oamSetHidden(oam(), 49, true);
    }

    oamUpdate(oam());

    auto time = currentTime();

    consoleSelect(&console_);
    consoleClear();

    console_.cursorX = (sub_ ? 1 : 25);
    console_.cursorY = (sub_ ? 22 : 1);
    printf("%0.2ld:%0.2ld", time.minutes, time.seconds);

    console_.cursorX = 10;
    console_.cursorY = (sub_ ? 22 : 1);
    printf("HP: %0.3ld/%0.3ld", currentHealth_, character_->maxHealth());

    // Enable the display after the first render
    if (sub_) {
        REG_DISPCNT_SUB |= MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
    } else {
        REG_DISPCNT |= MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
    }
}

bool Player::handleInputs() {
    auto keys = keysDown();
    if (!hasSelectedUnit() && (keys & (KEY_UP | KEY_DOWN | KEY_RIGHT | KEY_LEFT))) {
        selectedUnit_.x = 0;
        selectedUnit_.y = 0;
    } else {
        if (keys & KEY_UP) { selectedUnit_.y = selectedUnit_.y - 1; }
        if (keys & KEY_DOWN) { selectedUnit_.y = selectedUnit_.y + 1; }
        if (keys & KEY_LEFT) { selectedUnit_.x = selectedUnit_.x - 1; }
        if (keys & KEY_RIGHT) { selectedUnit_.x = selectedUnit_.x + 1; }
    }

    if (keys & KEY_B) {
        selectedUnit_.x = -1;
        selectedUnit_.y = -1;
    }

    if ((keys & KEY_A) || (sub_ && (keys & KEY_TOUCH))) {
        if ((keys & KEY_A)) {
            keyAPressedAt_ = timeAsMilliseconds();
        }


        if (sub_ && (keys & KEY_TOUCH)) {
            touchPosition pos = touchReadXY();

            if (IN_RANGE(pos.px, 16, 240) && IN_RANGE(pos.py, 0, 168)) {
                int x = (pos.px - 16) / 32;
                int y = pos.py / 32;

                if (selectedUnit_.x != x || selectedUnit_.y != y) {
                    touchScreenPressedAt_ = timeAsMilliseconds();
                }

                selectedUnit_.x = x;
                selectedUnit_.y = y;
            }
        }
    } else {
        uint64_t heldTime = 0;
        if (keyAPressedAt_ && !(keysHeld() & KEY_A)) {
            heldTime = timeAsMilliseconds() - keyAPressedAt_;
            keyAPressedAt_ = 0;
        }
        if (touchScreenPressedAt_ && !(keysHeld() & KEY_TOUCH)) {
            heldTime = timeAsMilliseconds() - touchScreenPressedAt_;
            touchScreenPressedAt_ = 0;
        }

        if (heldTime > 0) {
            selectedUnit_ = { -1, -1 };
            return true;
        }
    }
}

void Player::update() { }