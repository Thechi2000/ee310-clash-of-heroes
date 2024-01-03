#include "player.hpp"

Player::Player() : battleField_()
{
    battleField_.fill(nullptr);
}

Unit *&Player::at(int x, int y)
{
    battleField_[x + 8 * y];
}

Player::~Player()
{
    for (auto &i : battleField_)
    {
        if (i != nullptr)
        {
            delete i;
            i = nullptr;
        }
    }
}