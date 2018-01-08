#include <iostream>
#include <SDL2/SDL.h>
#include "SDLHelpers.hpp"

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;
const std::string WINDOW_NAME = "Snake";

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        CTG::LogSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *window = 
        SDL_CreateWindow(WINDOW_NAME.c_str(),
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         DEFAULT_WIDTH,
                         DEFAULT_HEIGHT,
                         SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        CTG::LogSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = 
        SDL_CreateRenderer(window,
                           -1,
                            SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == nullptr)
    {
        CTG::LogSDLError(std::cout, "SDL_CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //SDL_Texture *helloTex = CTG::LoadTextureBMP("hello.bmp", renderer);
    SDL_Texture *helloTex = CTG::LoadTexturePNG("hello.png", renderer);
    
    if(helloTex == nullptr)
    {
        SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    CTG::DrawTexture(helloTex, renderer, 0, 0);
    SDL_RenderPresent(renderer);

    for(int i = 0; i < 10; i++)
    {
        SDL_Delay(1000);
    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}