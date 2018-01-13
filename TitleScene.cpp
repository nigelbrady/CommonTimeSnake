#include <iostream>
#include <SDL2/SDL.h>
#include "TitleScene.hpp"
#include "Resources.hpp"
#include "SDLHelpers.hpp"

bool CTG::TitleScene::Event(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_SPACE:
                ChangeScene(CTG::Scene::gameScene);
                return true;
        }
    }

    return false;
}

void CTG::TitleScene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    DrawTitleAndSubtitle(CTG::Resources::titleText, CTG::Resources::subTitleText, ren);
}