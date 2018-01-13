#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace CTG
{
    const int LARGE_FONT_SIZE = 64;
    const int MEDIUM_FONT_SIZE = 32;
    const int SMALL_FONT_SIZE = 24;
    
    const std::string FONT_NAME = "assets/sample.ttf";

    const std::string TITLE_TEXT = "Snake!";
    const std::string SUBTITLE_TEXT = "Press Space to play!";

    const std::string PAUSED_TEXT = "Paused";
    const std::string CONTINUE_TEXT = "Press Space to continue!";

    const std::string GAME_OVER_TEXT = "Game Over!";
    const std::string RESTART_TEXT = "Press space to restart, ESC to quit";

    const SDL_Color TEXT_COLOR = { 255, 255, 255, 255 };

    class Resources
    {
        private:
            static bool OpenFonts();
            static void CloseFonts();

        public:
            static SDL_Texture *titleText;
            static SDL_Texture *subTitleText;

            static SDL_Texture *pausedText;
            static SDL_Texture *continueText;

            static SDL_Texture *gameOverText;
            static SDL_Texture *restartText;

            static TTF_Font *largeFont;
            static TTF_Font *mediumFont;
            static TTF_Font *smallFont;

            static bool LoadResources(SDL_Renderer *ren);
            static void DestroyResources();
    };
}
