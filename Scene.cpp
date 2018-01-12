#include <iostream>
#include <SDL2/SDL.h>
#include "Scene.hpp"

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
    std::cout << "Enter scene: " << name << std::endl;
}

void CTG::Scene::OnSceneEnded()
{
    std::cout << "Exit scene: " << name << std::endl;
}

CTG::Scene::Scene(std::string n)
{
    name = n;
}



