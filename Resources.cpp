#include <iostream>
#include "Resources.hpp"
#include "SDLHelpers.hpp"

SDL_Texture * CTG::Resources::titleText = nullptr;
SDL_Texture * CTG::Resources::subTitleText = nullptr;

SDL_Texture * CTG::Resources::pausedText = nullptr;
SDL_Texture * CTG::Resources::continueText = nullptr;

SDL_Texture * CTG::Resources::gameOverText = nullptr;
SDL_Texture * CTG::Resources::restartText = nullptr;

TTF_Font * CTG::Resources::largeFont = nullptr;
TTF_Font * CTG::Resources::mediumFont = nullptr;
TTF_Font * CTG::Resources::smallFont = nullptr;

void CloseFonts();

bool CTG::Resources::LoadResources(SDL_Renderer *ren)
{   
    if(!OpenFonts())
    {
        std::cout << "Error opening fonts...check resource paths!" << std::endl; 
        return false;
    } 

    titleText = CreateTextureFromString(CTG::TITLE_TEXT, largeFont, CTG::TEXT_COLOR, ren);

    if(titleText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating title text!");
        DestroyResources();
        return false;
    }

    subTitleText = CreateTextureFromString(CTG::SUBTITLE_TEXT, mediumFont, CTG::TEXT_COLOR, ren);

    if(titleText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating subtitle text!");
        DestroyResources();
        return false;
    }

    pausedText = CreateTextureFromString(CTG::PAUSED_TEXT, largeFont, CTG::TEXT_COLOR, ren);

    if(pausedText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating paused text!");
        DestroyResources();
        return false;
    }

    continueText = CreateTextureFromString(CTG::CONTINUE_TEXT, mediumFont, CTG::TEXT_COLOR, ren);

    if(continueText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating continue text!");
        DestroyResources();
        return false;
    }

    gameOverText = CreateTextureFromString(CTG::GAME_OVER_TEXT, largeFont, CTG::TEXT_COLOR, ren);

    if(gameOverText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating game over text!");
        DestroyResources();
        return false;
    }

    restartText = CreateTextureFromString(CTG::RESTART_TEXT, mediumFont, CTG::TEXT_COLOR, ren);
    
    if(restartText == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error creating restart text!");
        DestroyResources();
        return false;
    }

    CloseFonts();
    return true;
}

void CTG::Resources::DestroyResources()
{
    CloseFonts();

    if(titleText != nullptr)
    {
        SDL_DestroyTexture(titleText);
        titleText = nullptr;
    }

    if(subTitleText != nullptr)
    {
        SDL_DestroyTexture(subTitleText);
        subTitleText = nullptr;
    }

    if(pausedText != nullptr)
    {
        SDL_DestroyTexture(pausedText);
        pausedText = nullptr;
    }

    if(continueText != nullptr)
    {
        SDL_DestroyTexture(continueText);
        continueText = nullptr;
    }

    if(gameOverText != nullptr)
    {
        SDL_DestroyTexture(gameOverText);
        gameOverText = nullptr;
    }

    if(restartText != nullptr)
    {
        SDL_DestroyTexture(restartText);
        restartText = nullptr;
    }
}

bool CTG::Resources::OpenFonts()
{
    largeFont = TTF_OpenFont(CTG::FONT_NAME.c_str(), CTG::LARGE_FONT_SIZE);

    if(largeFont == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error loading large font!");
        return false;
    }

    mediumFont = TTF_OpenFont(CTG::FONT_NAME.c_str(), CTG::MEDIUM_FONT_SIZE);

    if(mediumFont == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error loading medium font!");
        CloseFonts();
        return false;
    }

    smallFont = TTF_OpenFont(CTG::FONT_NAME.c_str(), CTG::SMALL_FONT_SIZE);

    if(smallFont == nullptr)
    {
        CTG::LogSDLError(std::cout, "Error loading small font!");
        CloseFonts();
        return false;
    }

    return true;
}

void CTG::Resources::CloseFonts()
{
    if(largeFont != nullptr)
    {
        TTF_CloseFont(largeFont);
        largeFont = nullptr;
    }

    if(mediumFont != nullptr)
    {
        TTF_CloseFont(mediumFont);
        mediumFont = nullptr;
    }

    if(smallFont != nullptr)
    {
        TTF_CloseFont(smallFont);
        smallFont = nullptr;
    }
}