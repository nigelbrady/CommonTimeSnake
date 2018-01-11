#pragma once

#include <iostream>
#include <vector>
#include "SDLHelpers.hpp"

namespace CTG
{
    typedef SDL_GameObject SnakePiece;

    typedef enum direction_t {
        up,
        down,
        left,
        right
    } direction;

    class Snake
    {
    public:
        direction direction;
        std::vector<SnakePiece *> pieces;

        Snake()
        {
            pieces.reserve(10);
        }

        void Move(direction_t direction);
        void Grow();
        bool CheckDeath();
    };
}
