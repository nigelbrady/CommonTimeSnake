#include <iostream>
#include <SDL2/SDL.h>
#include "Scene.hpp"
#include "SDLHelpers.hpp"

int CTG::Scene::sceneWidth = 640;
int CTG::Scene::sceneHeight = 480;

CTG::Scene* CTG::Scene::currentScene = nullptr;
CTG::Scene* CTG::Scene::titleScene = nullptr;
CTG::Scene* CTG::Scene::gameScene = nullptr;

std::string CTG::Scene::GetName()
{
    return name;
}

bool CTG::Scene::Event(SDL_Event e)
{   
    return false;
}

void CTG::Scene::Update(int delta)
{
    
}

void CTG::Scene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderClear(ren);
}

void CTG::Scene::ChangeScene(CTG::Scene *nextScene)
{
    CTG::Scene *leaving = currentScene;

    if(leaving != nullptr)
    {
        leaving->OnSceneEnded();
    }

    nextScene -> OnSceneStarted();
    currentScene = nextScene;
}

void CTG::Scene::OnSceneStarted()
{
    //std::cout << "Enter scene: " << name << std::endl;
}

void CTG::Scene::OnSceneEnded()
{
    //std::cout << "Exit scene: " << name << std::endl;
}

CTG::Scene::Scene(std::string n)
{
    name = n;
}

void CTG::Scene::DrawTitleAndSubtitle(SDL_Texture *title, SDL_Texture *subTitle, SDL_Renderer *ren)
{
    /* Draw title, subtitle text */
    int tW, tH;
    int tX, tY;

    int sW, sH;
    int sX, sY;

    SDL_QueryTexture(title, nullptr, nullptr, &tW, &tH);
    SDL_QueryTexture(subTitle, nullptr, nullptr, &sW, &sH);

    tX = sceneWidth / 2 - tW / 2;
    tY = sceneHeight / 2 - tH / 2 - sH;

    sX = sceneWidth / 2 - sW / 2;
    sY = sceneHeight / 2 - sH / 2 + sH;

    DrawTexture(title, ren, tX, tY);
    DrawTexture(subTitle, ren, sX, sY);
}



