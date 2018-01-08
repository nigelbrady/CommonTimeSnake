#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLHelpers.hpp"

void CTG::LogSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture * CTG::LoadTextureBMP(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    if(loadedImage == nullptr)
    {
        CTG::LogSDLError(std::cout, "CTG::LoadTextureBMP::SDL_LoadBMP");
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);

    if(texture == nullptr)
    {
        CTG::LogSDLError(std::cout, "CTG::LoadTextureBMP::SDL_CreateTextureFromSurface");
        return nullptr;
    }

    return texture;
}

SDL_Texture * CTG::LoadTexturePNG(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture *tex = IMG_LoadTexture(renderer, file.c_str());
    
    if(tex == nullptr)
    {
        CTG::LogSDLError(std::cout, "IMG_LoadTexture");
    }

    return tex;
}

void CTG::DrawTexture(SDL_Texture *tex,
                      SDL_Renderer *ren,
                      SDL_Rect *clip,
                      int x,
                      int y,
                      int w,
                      int h)
{
   SDL_Rect destRect;
   destRect.x = x;
   destRect.y = y;

   if(w != 0 && h != 0)
   {
       destRect.w = w;
       destRect.h = h;
   }
   else if(clip != nullptr)
   {
       destRect.w = clip -> w;
       destRect.h = clip -> h;
   }
   else
   {
       SDL_QueryTexture(tex, NULL, NULL, &destRect.w, &destRect.h);
   }

   SDL_RenderCopy(ren, tex, clip, &destRect);
}

void CTG::DrawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
    CTG::DrawTexture(tex, ren, nullptr, x, y, w, h);
}