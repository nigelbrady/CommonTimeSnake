#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDLHelpers.hpp"
#include "Resources.hpp"
#include "Scene.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;
const std::string WINDOW_NAME = "Snake";

int main(int argc, char** argv)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if(CTG::StartSDL() != 0)
    {
        std::cout << "Error setting up SDL, quitting..." << std::endl;
    }

    window = 
        SDL_CreateWindow(WINDOW_NAME.c_str(),
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         DEFAULT_WIDTH,
                         DEFAULT_HEIGHT,
                         SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        CTG::LogSDLError(std::cout, "SDL_CreateWindow");
        CTG::FinishSDL(renderer, window);
        return 1;
    }

    renderer = 
        SDL_CreateRenderer(window,
                           -1,
                            SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == nullptr)
    {
        CTG::LogSDLError(std::cout, "SDL_CreateRenderer");
        CTG::FinishSDL(renderer, window);
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    int now = 0;
    int then = SDL_GetTicks();
    int deltaTime = 0;

    CTG::Scene::titleScene = new CTG::TitleScene();
    CTG::Scene::gameScene = new CTG::GameScene();
    CTG::Scene::currentScene = CTG::Scene::titleScene;

    CTG::Scene *cur = CTG::Scene::currentScene;

    while(!quit)
    {
        now = SDL_GetTicks();
        deltaTime = now - then;
        then = now;

        cur = CTG::Scene::currentScene;
        //std::cout << "deltaTime: " << deltaTime << std::endl;

        while(SDL_PollEvent(&e))
        {
            if(cur->Event(e)) 
            { 
                continue; 
            }
            else if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        cur->Update(deltaTime);
        cur->Draw(renderer);
        SDL_RenderPresent(renderer);
    }

    CTG::FinishSDL(renderer, window);
    return 0;
}


