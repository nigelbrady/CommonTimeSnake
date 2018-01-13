#include <iostream>
#include "GameScene.hpp"
#include "Snake.hpp"
#include "Resources.hpp"

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
                snake.direction = up;
                return true;

            case SDLK_s:
            case SDLK_DOWN:
                snake.direction = down;
                return true;

            case SDLK_a:
            case SDLK_LEFT:
                snake.direction = left;
                return true;

            case SDLK_d:
            case SDLK_RIGHT:
                snake.direction = right;
                return true;

            case SDLK_SPACE:
                if(state == running)
                {
                    state = paused;
                }
                else if(state == paused)
                {
                    state = running;
                }
                else if(state == game_over)
                {
                    ResetGame();
                }
                return true;

            default:
                return false;
        }
    }

    return false;
}

void CTG::GameScene::Update(int delta)
{
    if(state == running)
    {
        snake.Update(delta);

        if(snake.CheckDeath())
        {
            state = game_over;
        }
        else if(AppleEaten())
        {
            snake.Grow();
            PlaceApple();
        }
    }
}

void CTG::GameScene::Draw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    if(state == game_over)
    {
        DrawTitleAndSubtitle(CTG::Resources::gameOverText,
                             CTG::Resources::restartText,
                             ren);
    }
    else if(state == paused)
    {
        DrawTitleAndSubtitle(CTG::Resources::pausedText,
                             CTG::Resources::continueText,
                             ren);
    }
    else if(state == running)
    {
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &apple.bounds);

        for(int i = 0; i < snake.pieces.size(); i++)
        {
            SnakePiece *piece = snake.pieces[i];

            //std::cout << "W: " << piece->collisionRect.w << std::endl;
            //std::cout << "H: " << piece->collisionRect.h << std::endl;

            SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
            SDL_RenderFillRect(ren, &piece->bounds);
        }
    }
}

void CTG::GameScene::OnSceneStarted()
{
    CTG::Scene::Scene::OnSceneStarted();
    CTG::GameScene::ResetGame();
}

void CTG::GameScene::ResetGame()
{
    snake.direction = right;
    snake.pieces.clear();
    snake.targetLocations.clear();
    snake.Grow();

    PlaceApple();

    state = running;
}

void CTG::GameScene::PlaceApple()
{
    do
    {
        int randX = rand() % sceneWidth;
        int randY = rand() % sceneHeight;

        randX = std::max(randX, CTG::SEGMENT_SIZE);
        randY = std::max(randY, CTG::SEGMENT_SIZE);

        randX = std::min(randX, sceneWidth - CTG::SEGMENT_SIZE);
        randY = std::min(randY, sceneHeight - CTG::SEGMENT_SIZE);

        apple.bounds.x = randX;
        apple.bounds.y = randY;
        apple.bounds.w = CTG::SEGMENT_SIZE;
        apple.bounds.h = CTG::SEGMENT_SIZE;
        
    } while(snake.CheckCollision(apple.bounds));   
}

bool CTG::GameScene::AppleEaten()
{
    SnakePiece *head = snake.pieces[0];
    SDL_Rect ir;
    return SDL_IntersectRect(&head->bounds, &apple.bounds, &ir) == SDL_TRUE;
}

