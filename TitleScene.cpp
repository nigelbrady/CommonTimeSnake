#include <iostream>
#include <SDL2/SDL.h>
#include "TitleScene.hpp"

bool CTG::TitleScene::Event(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                return false;

            default:
                ChangeScene(CTG::Scene::gameScene);
                return true;
        }
    }

    return false;
}

void CTG::TitleScene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderClear(ren);
}