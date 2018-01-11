#pragma once

#include <iostream>
#include <vector>
#include "SDLHelpers.hpp"
 
namespace CTG
{
    typedef SDL_GameObject SnakePiece;

    extern const int SEGMENT_SIZE;

    typedef enum direction_t 
    {
        up,
        down,
        left,
        right
    } direction;

    class Snake
    {
        private:
            void UpdateTargetLocations();

        public:
            int velocity;
            direction direction;
            std::vector<SnakePiece *> pieces;
            std::vector<SDL_Point> targetLocations;

            Snake()
            {
                velocity = 20;
                pieces.reserve(10);
            }

            void Move(direction_t direction);
            void Update(int delta);
            void Grow();
            bool CheckDeath();
    };
}
