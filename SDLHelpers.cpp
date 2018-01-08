#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDLHelpers.hpp"

int CTG::StartSDL()
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

    return 0;
}

void CTG::FinishSDL(SDL_Renderer *ren, SDL_Window *win)
{
    if(ren != nullptr)
    {
        SDL_DestroyRenderer(ren);
    }
    if(win != nullptr)
    {
        SDL_DestroyWindow(win);
    }

    SDL_Quit();
}

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

SDL_Texture * CTG::CreateTextureFromString(const std::string &text,
                                           TTF_Font *font,
                                           SDL_Color color,
                                           SDL_Renderer *ren)
{
    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);

    if(surf == nullptr)
    {
        CTG::LogSDLError(std::cout, "TTF_RenderText_Blended");
        return nullptr;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);

    if(tex == nullptr)
    {
        CTG::LogSDLError(std::cout, "SDL_CreateTextureFromSurface");
    }

    SDL_FreeSurface(surf);
    return tex;
}

SDL_Texture * CTG::CreateTextureFromString(const std::string &text,
                                           const std::string &fontFile,
                                           SDL_Color color,
                                           int fontSize,
                                           SDL_Renderer *ren)
{
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);

    if(font == nullptr)
    {
        CTG::LogSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }

    SDL_Texture *tex = CTG::CreateTextureFromString(text, font, color, ren);

    TTF_CloseFont(font);
    return tex;
}                                         