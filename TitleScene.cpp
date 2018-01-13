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

    /* Draw title text */

    int tW, tH;
    int tX, tY;

    int sW, sH;
    int sX, sY;

    SDL_QueryTexture(CTG::Resources::titleText, nullptr, nullptr, &tW, &tH);
    SDL_QueryTexture(CTG::Resources::subTitleText, nullptr, nullptr, &sW, &sH);

    tX = sceneWidth / 2 - tW / 2;
    tY = sceneHeight / 2 - tH / 2 - sH;

    sX = sceneWidth / 2 - sW / 2;
    sY = sceneHeight / 2 - sH / 2 + sH;

    DrawTexture(CTG::Resources::titleText, ren, tX, tY);
    DrawTexture(CTG::Resources::subTitleText, ren, sX, sY);
}