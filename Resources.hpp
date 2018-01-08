#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace CTGResources
{
    class Resources
    {
        public:
            SDL_Texture *snakeHead;
            SDL_Texture *snakeBody;
            SDL_Texture *grassTexture;
            SDL_Texture *appleTexture;

            SDL_Texture *titleText;
            SDL_Texture *subTitleText;

            SDL_Texture *scoreText;
            SDL_Texture *pausedText;
            SDL_Texture *gameOverText;

            TTF_Font *largeFont;
            TTF_Font *mediumFont;
            TTF_Font *smallFont;

            Resources();
            ~Resources();

            bool success;
    };

    const std::string SNAKE_HEAD = "snake_head.png";
    const std::string SNAKE_BODY = "snake_body.png";
    const std::string GRASS_TEXTURE = "grass_texture.png";
    const std::string APPLE_TEXTURE = "apple_texture.png";
    const std::string FONT_NAME = "font.ttf";
    
    const int LARGE_FONT_SIZE = 64;
    const int MEDIUM_FONT_SIZE = 32;
    const int SMALL_FONT_SIZE = 24;

    Resources *res = nullptr;
}
