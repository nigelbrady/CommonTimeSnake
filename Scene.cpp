#include <iostream>
#include <SDL2/SDL.h>
#include "Scene.hpp"

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
    leaving->OnSceneEnded();

    currentScene = nextScene;
    nextScene -> OnSceneStarted();
}

void CTG::Scene::OnSceneStarted()
{

}

void CTG::Scene::OnSceneEnded()
{
    
}

CTG::Scene::Scene(std::string n)
{
    name = n;
}



