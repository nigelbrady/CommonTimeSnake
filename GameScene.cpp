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
                if(snake.direction != down)
                    snake.direction = up;
                return true;

            case SDLK_s:
            case SDLK_DOWN:
                if(snake.direction != up)
                    snake.direction = down;
                return true;

            case SDLK_a:
            case SDLK_LEFT:
                if(snake.direction != right)
                    snake.direction = left;
                return true;

            case SDLK_d:
            case SDLK_RIGHT:
                if(snake.direction != left)
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

void CTG::GameScene::DrawWalls(SDL_Renderer *ren)
{
    int widthSegments = sceneWidth / CTG::SEGMENT_SIZE;
    int heightSegments = sceneHeight / CTG::SEGMENT_SIZE;

    SDL_Rect wR;
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    for(int j = 0; j < heightSegments; j++)
    {
        for(int i = 0; i < widthSegments; i++)
        {
            if(i == 0 || i == widthSegments - 1 
                || j== 0 || j == heightSegments -1)
                {
            
                    wR.x = i * CTG::SEGMENT_SIZE;
                    wR.y = j * CTG::SEGMENT_SIZE;
                    wR.w = CTG::SEGMENT_SIZE;
                    wR.h = CTG::SEGMENT_SIZE;

                    SDL_RenderFillRect(ren, &wR);   
                }
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
        DrawWalls(ren);
        DrawTitleAndSubtitle(CTG::Resources::pausedText,
                             CTG::Resources::continueText,
                             ren);
    }
    else if(state == running)
    {
        DrawWalls(ren);

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
        /* Generate apples only on
           multiples of the segment size*/

        int maxXIndex = sceneWidth / CTG::SEGMENT_SIZE;
        int maxYIndex = sceneHeight / CTG::SEGMENT_SIZE;

        int randX = (rand() % maxXIndex) * CTG::SEGMENT_SIZE;
        int randY = (rand() % maxYIndex) * CTG::SEGMENT_SIZE;

        randX = std::max(randX, CTG::SEGMENT_SIZE);
        randY = std::max(randY, CTG::SEGMENT_SIZE);

        randX = std::min(randX, sceneWidth - 2 * CTG::SEGMENT_SIZE);
        randY = std::min(randY, sceneHeight - 2 * CTG::SEGMENT_SIZE);

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

