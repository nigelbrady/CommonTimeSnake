#include <iostream>
#include "GameScene.hpp"


bool CTG::GameScene::Event(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                ChangeScene(CTG::Scene::titleScene);
                return true;

            case SDLK_w:
            case SDLK_UP:
                return true;

            case SDLK_s:
            case SDLK_DOWN:
                return true;

            case SDLK_a:
            case SDLK_LEFT:
                return true;

            case SDLK_d:
            case SDLK_RIGHT:
                return true;

            case SDLK_SPACE:
                return true;

            default:
                return false;
        }
    }

    return false;
}

void CTG::GameScene::Update(int delta)
{

}

void CTG::GameScene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderClear(ren);
}

void CTG::GameScene::OnSceneStarted()
{

}

void CTG::GameScene::ResetGame()
{

}