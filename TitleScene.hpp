#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Scene.hpp"

namespace CTG
{
    class TitleScene : public Scene
    {
        public:
            TitleScene() : Scene("TitleScene") {}

            bool Event(SDL_Event e);
            void Draw(SDL_Renderer *ren);
    };
}