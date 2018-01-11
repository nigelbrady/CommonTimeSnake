#include <iostream>
#include "GameScene.hpp"

bool CTG::GameScene::Event(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                ChangeScene(CTG::Scene::titleScene);
                return true;

            case SDLK_w:
            case SDLK_UP:
                snake.direction = direction_t::up;
                return true;

            case SDLK_s:
            case SDLK_DOWN:
                snake.direction = direction_t::down;
                return true;

            case SDLK_a:
            case SDLK_LEFT:
                snake.direction = direction_t::left;
                return true;

            case SDLK_d:
            case SDLK_RIGHT:
                snake.direction = direction_t::right;
                return true;

            case SDLK_SPACE:
                snake.Grow();
                return true;

            default:
                return false;
        }
    }

    return false;
}

void CTG::GameScene::Update(int delta)
{
    if(state == game_state_t::running)
    {
        /* 
        remainingCrawlTime -= (delta/1000.0f);

        if(remainingCrawlTime <= 0)
        {
            snake.Move(snake.direction);
            remainingCrawlTime = crawlTime;
        }
        */

        snake.Update(delta);

        if(snake.CheckDeath())
        {
            state = game_state_t::game_over;
        }
    }
}

void CTG::GameScene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    for(int i = 0; i < snake.pieces.size(); i++)
    {
        SnakePiece *piece = snake.pieces[i];

        //std::cout << "W: " << piece->collisionRect.w << std::endl;
        //std::cout << "H: " << piece->collisionRect.h << std::endl;

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &piece->bounds);
    }
}

void CTG::GameScene::OnSceneStarted()
{
    CTG::Scene::Scene::OnSceneStarted();
    CTG::GameScene::ResetGame();
}

void CTG::GameScene::ResetGame()
{
    score = 0;

    crawlTime = 0.10;
    remainingCrawlTime = crawlTime;

    snake.direction = direction::right;
    snake.pieces.clear();
    snake.Grow();
    
    apples.clear();
    spikes.clear();

    state = game_state_t::running;
}