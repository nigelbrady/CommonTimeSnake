#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace CTG
{
    /* Sprites and objects */

    typedef struct SDL_Sprite_st
    {
        SDL_Texture *texture;
        SDL_Rect region;
    } 
    SDL_Sprite;

    typedef struct SDL_GameObject_st
    {
        SDL_Sprite *sprite;
        SDL_Rect bounds;
        float x_pos_float;
        float y_pos_float;
    } 
    SDL_GameObject;

    typedef struct SDL_Point_Float_t
    {
        float x;
        float y;
    }
    SDL_Point_Float;

    void SDL_DrawSprite(SDL_Sprite& sp, SDL_Renderer *ren, int x, int y);
    bool SDL_CheckCollision(const SDL_Rect& first, const SDL_Rect& second);
    
    /* SDL Init and Cleanup */
    int StartSDL();
    void FinishSDL(SDL_Renderer *ren, SDL_Window *win);

    /* Texture loaders */
    SDL_Texture * LoadTextureBMP(const std::string &file, SDL_Renderer *renderer);
    SDL_Texture * LoadTexturePNG(const std::string &file, SDL_Renderer *renderer);

    /* Drawing helpers */
    void DrawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w=0, int h=0);
    void DrawTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect *clip,
                     int x, int y, int w=0, int h=0);

    /* Text drawing helpers */
    SDL_Texture * CreateTextureFromString(const std::string &text,
                                          TTF_Font *font,
                                          SDL_Color color,
                                          SDL_Renderer *ren);

    SDL_Texture * CreateTextureFromString(const std::string &text,
                                          const std::string &fontFile,
                                          SDL_Color color,
                                          int fontSize,
                                          SDL_Renderer *ren);                                      

    /* Logging helpers */
    void LogSDLError(std::ostream &os, const std::string &msg);
}
