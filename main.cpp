#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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

    if (TTF_Init() != 0)
    {
	    CTG::LogSDLError(std::cout, "TTF_Init");
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
    SDL_Texture *helloTex = CTG::LoadTexturePNG("circles.png", renderer);

    if(helloTex == nullptr)
    {
        SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int iW = 100, iH = 100;
    int x = DEFAULT_WIDTH / 2 - iW / 2;
    int y = DEFAULT_HEIGHT / 2 - iH / 2;

    SDL_Rect clips[4];

    for(int i = 0; i < 4; i++)
    {
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }

    int useClip = 0;

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
                switch(e.key.keysym.sym)
                {
                    case SDLK_1:
                        useClip = 0;
                        break;

                    case SDLK_2:
                        useClip = 1;
                        break;

                    case SDLK_3:
                        useClip = 2;
                        break;

                    case SDLK_4:
                        useClip = 3;
                        break;
                    
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        CTG::DrawTexture(helloTex, renderer, &clips[useClip], x, y);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}