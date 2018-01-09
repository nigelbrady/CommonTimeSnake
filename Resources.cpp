#include <iostream>
#include <SDL2/SDL.h>
#include "Resources.hpp"
#include "Scene.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"

bool CTG::LoadResources()
{
    return true;
}

void CTG::DestroyResources()
{

}

bool CTG::LoadScenes()
{
    CTG::Scene::titleScene = new CTG::TitleScene();
    CTG::Scene::gameScene = new CTG::GameScene();
    CTG::Scene::currentScene = CTG::Scene::titleScene;
    return true;
}

void CTG::DestroyScenes()
{
    if(CTG::Scene::titleScene != nullptr)
        delete CTG::Scene::titleScene;
    
    if(CTG::Scene::gameScene != nullptr)
        delete CTG::Scene::gameScene;
}