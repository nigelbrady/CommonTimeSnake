#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Scene.hpp"

namespace CTG
{
    class GameScene : public Scene
    {
        public:
            GameScene() : Scene("GameScene") {}

            bool Event(SDL_Event e);
            void Update(int delta);
            void Draw(SDL_Renderer *ren);

            void OnSceneStarted();

            void ResetGame();
    };
}