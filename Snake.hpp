#pragma once

#include <iostream>
#include <vector>
#include "SDLHelpers.hpp"
 
typedef enum direction_t {
    up,
    down,
    left,
    right
} direction;

typedef struct target_location_st{
    float current_time;
    float max_time;

    float from_x;
    float from_y;

    float to_x;
    float to_y;
} target_location;

namespace CTG
{
    typedef SDL_GameObject SnakePiece;

    extern const int SEGMENT_SIZE;

    class Snake
    {
        private:
            void UpdateTargetLocations();

        public:
            int velocity;
            direction direction;
            std::vector<SnakePiece *> pieces;
            std::vector<target_location *> targetLocations;

            Snake()
            {
                velocity = 10;
                pieces.reserve(10);
            }

            void Move(direction_t direction);
            void Update(int delta);
            void Grow();
            bool CheckDeath();
            bool CheckCollision(SDL_Rect& rect, bool includeHead=true);
    };
}
