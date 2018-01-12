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
                //snake.Grow();
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
        apple.bounds.x = rand() % sceneWidth - CTG::SEGMENT_SIZE;
        apple.bounds.y = rand() % sceneHeight - CTG::SEGMENT_SIZE;
    } while(snake.CheckCollisionWithSnake(apple.bounds));

    apple.bounds.w = CTG::SEGMENT_SIZE;
    apple.bounds.h = CTG::SEGMENT_SIZE;
}

bool CTG::GameScene::AppleEaten()
{
    SnakePiece *head = snake.pieces[0];
    SDL_Rect ir;
    return SDL_IntersectRect(&head->bounds, &apple.bounds, &ir) == SDL_TRUE;
}
