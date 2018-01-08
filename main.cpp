#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
	    CTG::LogSDLError(std::cout, "IMG_Init");
	    SDL_Quit();
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
    SDL_Texture *helloTex = CTG::LoadTexturePNG("image.png", renderer);

    if(helloTex == nullptr)
    {
        SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        CTG::DrawTexture(helloTex, renderer, 0, 0);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}