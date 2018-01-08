#include <iostream>
#include <SDL2/SDL.h>

namespace CTG
{
    /* Texture loaders */
    SDL_Texture * LoadTextureBMP(const std::string &file, SDL_Renderer *renderer);
    SDL_Texture * LoadTexturePNG(const std::string &file, SDL_Renderer *renderer);

    /* Drawing helpers */
    void DrawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w=0, int h=0);

    /* Logging helpers */
    void LogSDLError(std::ostream &os, const std::string &msg);
}
