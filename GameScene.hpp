#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SDLHelpers.hpp"
#include "Scene.hpp"
#include "Snake.hpp"

typedef enum game_state_t {
    running,
    paused,
    game_over
} game_state;

namespace CTG
{

typedef SDL_GameObject SnakePiece;

class GameScene : public Scene
{
  private:
    game_state state;
    
    Snake snake;

    SDL_GameObject apple;

    void PlaceApple();
    bool AppleEaten();
    
  public:
    GameScene() : Scene("GameScene"){}

    bool Event(SDL_Event e);
    void Update(int delta);
    void Draw(SDL_Renderer *ren);

    void OnSceneStarted();

    void ResetGame();
};
}