#include "player.hpp"
#include "sylvanUnits.h"
#include "sylvanBg.h"

#define SPRITE_SIZE (32 * 32)

class TestUnit : public Unit
{
public:
    virtual ~TestUnit() {}

    TestUnit(int x, int y, int spriteId) : Unit(x, y, 3, 6, 4, spriteId) {}

    void onTransformToAttack() {}
    void onTransformToWall() {}
    bool updateCharge() {}
};

Player::Player()
{
    battleField_.fill(nullptr);

    // TODO REMOVE
    static bool isMe = false;
    me_ = isMe;
    isMe = true;

    for (int i = 0; i < 48; ++i)
    {
        battleField_[i] = new TestUnit(1, 1, i % 9);
    }
    // END REMOVE

    if (me_)
    {
        VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
        REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
        BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

        dmaCopy(sylvanBgBitmap, BG_BMP_RAM_SUB(0), sylvanBgBitmapLen);
        dmaCopy(sylvanBgPal, BG_PALETTE_SUB, sylvanBgPalLen);

        bgTransform[6]->hdx = -1 * 256;
        bgTransform[6]->vdx = 0 * 256;
        bgTransform[6]->hdy = 0 * 256;
        bgTransform[6]->vdy = -1 * 256;
        bgTransform[6]->dx = 255 * 256;
        bgTransform[6]->dy = 191 * 256;

        VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
        swiCopy(pal(), SPRITE_PALETTE_SUB, palLen() / 2);
    }
    else
    {
        VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
        REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;
        BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

        dmaCopy(sylvanBgBitmap, BG_BMP_RAM(0), sylvanBgBitmapLen);
        dmaCopy(sylvanBgPal, BG_PALETTE, sylvanBgPalLen);

        bgTransform[2]->hdx = 1 * 256;
        bgTransform[2]->vdx = 0 * 256;
        bgTransform[2]->hdy = 0 * 256;
        bgTransform[2]->vdy = 1 * 256;
        bgTransform[2]->dx = 0 * 256;
        bgTransform[2]->dy = 0 * 256;

        VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE;
        swiCopy(pal(), SPRITE_PALETTE, palLen() / 2);
    }

    oamInit(oam(), SpriteMapping_1D_128, false);

    for (int i = 0; i < tilesLen() / SPRITE_SIZE; ++i)
    {
        auto gfx = oamAllocateGfx(oam(), SpriteSize_32x32, SpriteColorFormat_256Color);
        spritesGfx_.push_back(gfx);
        swiCopy(tiles() + i * SPRITE_SIZE, gfx, SPRITE_SIZE / 2);
    }
}

Unit *&Player::at(int x, int y)
{
    return battleField_[x + 8 * y];
}

OamState *Player::oam() const
{
    return me_ ? &oamSub : &oamMain;
}
const void *Player::tiles() const { return sylvanUnitsTiles; }
size_t Player::tilesLen() const { return sylvanUnitsTilesLen; }
const void *Player::pal() const { return sylvanUnitsPal; }
size_t Player::palLen() const { return sylvanUnitsPalLen; }

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

                auto spriteId = unit->getSpriteIdAt(relativePosition);
                oamSet(
                    oam(),
                    x + y * 8,
                    x * 28 + 16, y * 28 + (me_ ? 0 : 20),
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
        }
    }

    oamUpdate(oam());
}

void Player::update() {}

Player::~Player()
{
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
