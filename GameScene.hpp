#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "Scene.hpp"
#include "SDLHelpers.hpp"

namespace CTG
{
    typedef enum direction_t
    {
        up,
        down,
        left,
        right
    }
    direction;

    typedef enum game_state_t
    {
        running,
        paused,
        game_over
    }
    game_state;

    typedef SDL_GameObject SnakePiece;

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
    
    class GameScene : public Scene
    {
        private:
            game_state state;

            int score;

            Snake snake;

            float remainingCrawlTime;
            float crawlTime;

            std::vector<SDL_GameObject> apples;
            std::vector<SDL_GameObject> spikes;

        public:
            GameScene() : Scene("GameScene")
            {
                ResetGame();
            }

            bool Event(SDL_Event e);
            void Update(int delta);
            void Draw(SDL_Renderer *ren);

            void OnSceneStarted();

            void ResetGame();
    };
}