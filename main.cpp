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

    //SDL_Texture *helloTex = CTG::LoadTextureBMP("hello.bmp", renderer);
    SDL_Texture *helloTex = CTG::LoadTexturePNG("circles.png", renderer);

    if(helloTex == nullptr)
    {
        CTG::FinishSDL(renderer, window);
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

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture *textImage = 
        CTG::CreateTextureFromString("Hello, World",
                                     "sample.ttf",
                                     color,
                                     64,
                                      renderer);

    if(textImage == nullptr)
    {
        CTG::FinishSDL(renderer, window);
        return 1;
    }

    int tW, tH;
    SDL_QueryTexture(textImage, NULL, NULL, &tW, &tH);
    int tx = DEFAULT_WIDTH / 2 - tW / 2;
    int ty = DEFAULT_HEIGHT / 2 - tH / 2;

    SDL_Event e;
    bool quit = false;

    int now = 0;
    int then = SDL_GetTicks();
    int deltaTime = 0;

    while(!quit)
    {
        now = SDL_GetTicks();
        deltaTime = now - then;
        then = now;

        //std::cout << "deltaTime: " << deltaTime << std::endl;

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
        CTG::DrawTexture(textImage, renderer, tx, ty);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(helloTex);
    SDL_DestroyTexture(textImage);
    CTG::FinishSDL(renderer, window);
    return 0;
}