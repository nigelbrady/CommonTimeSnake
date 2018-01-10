#include <iostream>
#include "GameScene.hpp"

CTG::SnakePiece * InitSnakePiece();
CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece);

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
                return true;

            case SDLK_s:
            case SDLK_DOWN:
                return true;

            case SDLK_a:
            case SDLK_LEFT:
                return true;

            case SDLK_d:
            case SDLK_RIGHT:
                return true;

            case SDLK_SPACE:
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

    snake.velocity = 10;
    snake.direction = direction::right;
    snake.pieces.clear();
    snake.Grow();
    
    apples.clear();
    spikes.clear();

    state = game_state_t::running;
}

void CTG::Snake::Grow()
{
    SnakePiece *piece; 
    
    if(pieces.empty())
    {
        piece = InitSnakePiece();
        std::cout << "Head: " << piece->bounds.x << ", " << piece->bounds.y << "Size: " << pieces.size() << std::endl;
    }
    else
    {
        SnakePiece *back = pieces.back();
        piece = InitSnakePiece(back);
    }

    pieces.push_back(piece);
}

bool CTG::Snake::CheckDeath()
{
    return false;
}

void CTG::Snake::Update(int delta)
{
    float dx, dy;
    float dt = delta/1000.0f;

    switch(direction)
    {
        case direction_t::up:
            dx = 0;
            dy = 1;
            break;

        case direction_t::down:
            dx = 0;
            dy = -1;
            break;

        case direction_t::left:
            dx = -1;
            dy = 0;
            break;

        case direction_t::right:
            dx = 1;
            dy = 0;
            break;
    }

    float last_pos_x = 0;
    float last_pos_y = 0;

    for(int i = 0; i < pieces.size(); i++)
    {
        SnakePiece *piece = pieces[i];

        if(i == 0)
        {
            float oldX = piece->x_pos_float;
            float oldY = piece->y_pos_float;

            piece->x_pos_float +=  dx * velocity * dt;
            piece->y_pos_float +=  dy * velocity * dt;

            std::cout << "Old pos (" << oldX << "," << oldY << ")" << ", new pos (" << piece->x_pos_float << "," << piece->y_pos_float << ")" << std::endl;
        }
        else
        {
            piece->x_pos_float = last_pos_x;
            piece->y_pos_float = last_pos_y;
        }

        piece->bounds.x = (int)piece->x_pos_float;
        piece->bounds.y = (int)piece->y_pos_float;

        last_pos_x = piece->x_pos_float;
        last_pos_y = piece->y_pos_float;
    }
}

CTG::SnakePiece * InitSnakePiece()
{
    CTG::SnakePiece *piece = new CTG::SnakePiece;

    piece->sprite = nullptr;

    piece->bounds.x = 640 / 2;
    piece->bounds.y = 480 / 2;
    piece->x_pos_float = piece->bounds.x;
    piece->y_pos_float = piece->bounds.y;
    piece->bounds.w = 16;
    piece->bounds.h = 16;

    return piece;
}

CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece)
{
    CTG::SnakePiece *piece = new CTG::SnakePiece;

    piece->sprite = nullptr;

    piece->bounds.x = priorPiece->bounds.x;
    piece->bounds.y = priorPiece->bounds.y;
    piece->bounds.w = priorPiece->bounds.w;
    piece->bounds.h = priorPiece->bounds.h;
    piece->x_pos_float = priorPiece->x_pos_float;
    piece->y_pos_float = priorPiece->y_pos_float;

    return piece;
}