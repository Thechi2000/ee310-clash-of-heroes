#include "player.hpp"
#include "army.hpp"
#include "haven.hpp"

#define SPRITE_SIZE (32 * 32)

class TestUnit : public Unit
{
public:
    virtual ~TestUnit() {}

    TestUnit(int x, int y, Player *player, UnitType unitType, ColorType colorType, int spriteId) : Unit(x, y, 3, 6, 4, player, unitType, colorType, spriteId) {}

    void onTransformToAttack() {}
    void onTransformToWall() {}
    bool updateCharge() {}
};

Player::Player(Faction faction, bool sub) : character_(Character::fromFaction(faction)),
                                            selectedUnit_{-1, -1},
                                            sub_(sub)
{
    battleField_.fill(nullptr);

    for (int i = 0; i < 48; ++i)
    {
        battleField_[i] = new TestUnit(1, 1, this, UnitType::Swordsman, static_cast<ColorType>(i % 3), i % 9 + 1);
    }
    // END REMOVE
}

void Player::init()
{
    consoleInit(&console_, 0, BgType_Text4bpp, BgSize_T_256x256, 8, 0, !sub_, true);

    if (sub_)
    {
        VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
        REG_DISPCNT_SUB = 0; // Disable the display to avoid clutter on the screen while loading the different assets
        BGCTRL_SUB[2] = BG_BMP_BASE(4) | BgSize_B8_256x256;

        mdCopy(BG_BMP_RAM_SUB(4), character_->bgBmp, character_->bgBmpLen, [](u8 a, size_t i, u8 *array)
               {
            while (array[i] == 255) { i--; }
            return array[i]; });
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
    }
    else
    {
        VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
        REG_DISPCNT = 0; // Disable the display to avoid clutter on the screen while loading the different assets
        BGCTRL[2] = BG_BMP_BASE(4) | BgSize_B8_256x256;

        mdCopy(BG_BMP_RAM(4), character_->bgBmp, character_->bgBmpLen, [](u8 a, size_t i, u8 *array)
               {
            while (array[i] == 255) { i--; }
            return array[i]; });
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

    for (int i = 0; i < character_->spriteTilesLen / SPRITE_SIZE; ++i)
    {
        auto gfx = oamAllocateGfx(oam(), SpriteSize_32x32, SpriteColorFormat_256Color);
        spritesGfx_.push_back(gfx);
        swiCopy(character_->spriteTiles + i * SPRITE_SIZE, gfx, SPRITE_SIZE / 2);
    }
}

Player::~Player()
{
    delete character_;

    for (size_t i = 0; i < battleField_.size(); ++i)
    {
        auto unit = battleField_[i];

        if (unit != nullptr)
        {
            for (size_t x = 0; x < unit->getSize().x; ++x)
            {
                for (size_t y = 0; y < unit->getSize().y; ++y)
                {
                    at(x, y) = nullptr;
                }
            }

            delete unit;
        }
    }

    for (auto gfx : spritesGfx_)
    {
        oamFreeGfx(oam(), gfx);
    }
}

Unit *&Player::at(int x, int y)
{
    return battleField_[x + 8 * y];
}

OamState *Player::oam() const
{
    return sub_ ? &oamSub : &oamMain;
}

bool Player::hasSelectedUnit() const { return selectedUnit_.x != -1 && selectedUnit_.y != -1; }

void Player::render()
{
    for (size_t x = 0; x < 8; ++x)
    {
        for (size_t y = 0; y < 6; ++y)
        {
            auto unit = at(x, y);
            if (unit != nullptr)
            {
                Vector relativePosition{.x = 0, .y = 0};
                while (at(x - relativePosition.x, y) == unit)
                {
                    ++relativePosition.x;
                }
                relativePosition.x--;

                while (at(x - relativePosition.x, y - relativePosition.y) == unit)
                {
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
                    false);
            }
            else
            {
                oamSetHidden(oam(), x + y * 8, true);
            }
        }
    }

    if (hasSelectedUnit() && at(selectedUnit_.x, selectedUnit_.y) == nullptr)
    {
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
            false);
    }
    else
    {
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
    if (sub_)
    {
        REG_DISPCNT_SUB |= MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
    }
    else
    {
        REG_DISPCNT |= MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
    }
}

bool Player::handleInputs()
{
    auto keys = keysDown();
    if (!hasSelectedUnit() && (keys & (KEY_UP | KEY_DOWN | KEY_RIGHT | KEY_LEFT)))
    {
        selectedUnit_.x = 0;
        selectedUnit_.y = 0;
    }
    else
    {
        if (keys & KEY_UP)
        {
            selectedUnit_.y = selectedUnit_.y - 1;
        }
        if (keys & KEY_DOWN)
        {
            selectedUnit_.y = selectedUnit_.y + 1;
        }
        if (keys & KEY_LEFT)
        {
            selectedUnit_.x = selectedUnit_.x - 1;
        }
        if (keys & KEY_RIGHT)
        {
            selectedUnit_.x = selectedUnit_.x + 1;
        }
    }

    if (keys & KEY_B)
    {
        selectedUnit_.x = -1;
        selectedUnit_.y = -1;
    }

    if ((keys & KEY_A) || (sub_ && (keys & KEY_TOUCH)))
    {
        if ((keys & KEY_A))
        {
            keyAPressedAt_ = timeAsMilliseconds();
        }

        if (sub_ && (keys & KEY_TOUCH))
        {
            touchPosition pos = touchReadXY();

            if (IN_RANGE(pos.px, 16, 240) && IN_RANGE(pos.py, 0, 168))
            {
                int x = (pos.px - 16) / 32;
                int y = pos.py / 32;

                if (selectedUnit_.x != x || selectedUnit_.y != y)
                {
                    touchScreenPressedAt_ = timeAsMilliseconds();
                }

                selectedUnit_.x = x;
                selectedUnit_.y = y;
            }
        }
    }
    else
    {
        uint64_t heldTime = 0;
        if (keyAPressedAt_ && !(keysHeld() & KEY_A))
        {
            heldTime = timeAsMilliseconds() - keyAPressedAt_;
            keyAPressedAt_ = 0;
        }
        if (touchScreenPressedAt_ && !(keysHeld() & KEY_TOUCH))
        {
            heldTime = timeAsMilliseconds() - touchScreenPressedAt_;
            touchScreenPressedAt_ = 0;
        }

        if (heldTime > 0)
        {
            selectedUnit_ = {-1, -1};
            return true;
        }
    }
}

void Player::handleDisparition(int battlefieldPosition)
{

    Unit *u = battleField_[battlefieldPosition];
    UnitType uT = u->getType();

    if (uT == None)
    {
        return;
    }
    if (uT == army_.specialA || uT == army_.specialB)
    {
        size_t x = battleField_[battlefieldPosition]->getSize().x;
        size_t y = battleField_[battlefieldPosition]->getSize().y;

        int minX = (battlefieldPosition / 8 - x < 0) ? 0 : battlefieldPosition / 8 - x;
        int minY = (battlefieldPosition % 6 - y < 0) ? 0 : battlefieldPosition % 6 - y;
        int maxX = (battlefieldPosition / 8 + x >= 8) ? 7 : battlefieldPosition / 8 + x;
        int maxY = (battlefieldPosition % 6 + y >= 6) ? 5 : battlefieldPosition % 6 + y;

        for (int i = minY; i < maxY; i++)
        {
            for (int j = minX; j < maxX; j++)
            {
                if (battleField_[battlefieldPosition + i + 8 * j] == u)
                {
                    battleField_[battlefieldPosition + i + 8 * j] = nullptr;
                }
            }
        }
    }
    else
    {
        if (u->getIsCharging())
        {
            for (int i = std::max(battlefieldPosition % 6 - 3, 0); i < std::max(battlefieldPosition % 6 + 3, 6); ++i)
            {
                if (battleField_[battlefieldPosition + i] == u)
                {
                    battleField_[battlefieldPosition + i] = nullptr;
                }
            }
        }
        battleField_[battlefieldPosition] = nullptr;
    }

    delete u;
}

void Player::updateBattleField()
{
    bool isChanged = true;
    while (isChanged)
    {
        bool isChanged = false;

        for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 6; ++y)
            {
                Unit *u = battleField_[8 * x + y];
                if (u != nullptr)
                {
                    UnitType uT = u->getType();
                    // Core Units
                    if (uT == army_.soldierA || uT == army_.soldierB || uT == army_.soldierC)
                    {
                        if (u->getIsCharging())
                        {
                            // Core unit is charging + fusion
                            y += 2;

                            // Core Unit fusion
                            Unit *uF = battleField_[8 * x + y - 3];
                            if (y > 2 && u->isEqual(uF))
                            {
                                u->onFusion(uF);
                                y += 3;
                                delete uF;
                                isChanged = true;
                            }
                        }
                        else
                        {
                            // Core Unit to wall
                            if (x < 6 && u->isEqual(battleField_[8 * x + y + 8]) && u->isEqual(battleField_[8 * x + y + 16]))
                            {
                                int i = x;
                                while (i < 8 && u->isEqual(battleField_[8 * i + y]))
                                {
                                    delete u;
                                    battleField_[8 * i + y] = new HavenWall(this);
                                }
                            }

                            // Core unit to charge
                            if (y < 4 && u->isEqual(battleField_[8 * x + y + 1]) && u->isEqual(battleField_[8 * x + y + 2]))
                            {
                                startCoreUnitCharge(8 * x + y);
                                y += 2;
                            }
                        }
                    }
                    if ((uT == army_.specialA || uT == army_.specialB) && (y < 3))
                    {
                        Vector size = u->getSize();
                        Unit *u1 = battleField_[8 * x + y + 2];
                        Unit *u2 = battleField_[8 * x + y + 3];
                        if (u1 != nullptr && u1->isEqual(u2) && u->getColor() == u1->getColor() && u1 != u2)
                        {
                            // Elite Unit
                            if (size.x == 1)
                            {
                                delete u1;
                                delete u2;
                                battleField_[8 * x + y + 2] = nullptr;
                                battleField_[8 * x + y + 3] = nullptr;
                                u->onTransformToAttack();
                                isChanged = true;
                            }
                            // Champion Unit
                            if (size.x == 2)
                            {
                                Unit *u3 = battleField_[8 * x + y + 8 + 2];
                                Unit *u4 = battleField_[8 * x + y + 8 + 3];
                                if (u1->isEqual(u3) && u->getColor() == u3->getColor() && u3 != u4)
                                {
                                    delete u1;
                                    delete u2;
                                    delete u3;
                                    delete u4;
                                    battleField_[8 * x + y + 2] = nullptr;
                                    battleField_[8 * x + y + 3] = nullptr;
                                    battleField_[8 * x + y + 8 + 2] = nullptr;
                                    battleField_[8 * x + y + 8 + 3] = nullptr;
                                    u->onTransformToAttack();
                                    isChanged = true;
                                }
                            }
                        }
                        y += 2;
                    }
                    if (uT == army_.wall)
                    {
                        Unit *uW = battleField_[8 * x + y + 1];
                        if (uW != nullptr && uW->getType() == uT)
                        {
                            static_cast<Wall *>(u)->onCombination(static_cast<Wall *>(uW), 8 * x + y + 1);
                            isChanged = true;
                            y += 1;
                        }
                    }
                }
            }
        }

        // Move units if necessery
        for (int x = 0; x < 8; ++x)
        {
            Unit *arr[6] = {nullptr};

            // Filling with champion unit needed
            if (x > 0)
            {
                for (int j = 0; j < 6; j++)
                {
                    if (battleField_[8 * x + j - 8] != nullptr && battleField_[8 * x + j - 8]->getSize().x == 2)
                    {
                        if (x == 1)
                        {
                            arr[j] = battleField_[8 * x + j - 8];
                        }
                        else if (battleField_[8 * x + j - 8] != battleField_[8 * x + j - 16])
                        {
                            arr[j] = battleField_[8 * x + j - 8];
                        }
                    }
                }
            }

            int i = 0;
            int j = 0;

            // Place Walls
            while (j < 6)
            {
                if (battleField_[8 * x + j] != nullptr && battleField_[8 * x + j]->getType() == army_.wall)
                {
                    if (i < 6)
                    {
                        arr[i] = battleField_[8 * x + j];
                        i += (i == 5 || arr[i + 1] == nullptr) ? 1 : 3;
                        isChanged = true;
                    }
                }
                j++;
            }

            // Place Charging Units
            j = 0;
            while (j < 6)
            {
                Unit *uM = battleField_[8 * x + j];
                if (uM != nullptr && uM->getIsCharging())
                {
                    // Core Unit Type
                    if (uM->getType() == army_.soldierA || uM->getType() == army_.soldierB || uM->getType() == army_.soldierC)
                    {
                        while (i < 4 && arr[i] != nullptr && arr[i + 1] != nullptr && arr[i+2] != nullptr) {
                            i += 1;
                        }

                        if (i < 4 && arr[i] != nullptr && arr[i + 1] != nullptr && arr[i+2] != nullptr)
                        {
                            arr[i] = uM;
                            arr[i + 1] = uM;
                            arr[i + 2] = uM;
                        }
                        j += 2;
                        isChanged = true;
                    }

                    // Elite and Champion Unit Type
                    if (uM->getSize().y == 2)
                    {
                        while (i < 5 && arr[i] != nullptr && arr[i + 1] != nullptr) {
                            i += 1;
                        }

                        if (i < 5 && arr[i] != nullptr && arr[i + 1] != nullptr)
                        {
                            arr[i] = uM;
                            arr[i + 1] = uM;
                        }
                        j += 1;
                        isChanged = true;
                    }

                    while (i < 6 && arr[i] != nullptr) {
                        ++i;
                    }
                }
                j++;
            }

            j = 0;
            while (i < 6 && j < 6)
            {
                if (battleField_[8 * x + j] != nullptr && !battleField_[8 * x + j]->getIsCharging() && !(battleField_[8 * x + j]->getType() == army_.wall))
                {
                    if (battleField_[8 * x + j]->getSize().y == 1) {
                        // Core non charging units
                        arr[i] = battleField_[8 * x + j];
                        isChanged = true;
                    } else {
                        // Elite and Champion non charging units
                        if (j < 5 && i < 5) {
                            arr[i] = battleField_[8 * x + j];
                            arr[i+1] = battleField_[8 * x + j + 1];
                        }
                        isChanged = true;
                        j++;
                    }
                }
            }

            // Copying the result in the original battlefield
            for (int y = 0; y < 6; ++y) {
                battleField_[8 * x + y] = arr[y];
            }
        }
    }
}

void Player::startCoreUnitCharge(int battlefieldPosition)
{
    int y = battlefieldPosition % 6;
    Unit *u = battleField_[battlefieldPosition];
    if (battlefieldPosition > 3 || u == nullptr || !u->isEqual(battleField_[battlefieldPosition + 1]) || !u->isEqual(battleField_[battlefieldPosition + 2]))
    {
        return;
    }

    u->onTransformToAttack();
    delete battleField_[battlefieldPosition + 1];
    delete battleField_[battlefieldPosition + 2];
    battleField_[battlefieldPosition + 1] = u;
    battleField_[battlefieldPosition + 2] = u;
}

void Player::update() {}