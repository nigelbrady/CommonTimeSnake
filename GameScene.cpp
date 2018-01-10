#include <iostream>
#include "GameScene.hpp"

CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece, CTG::direction_t direction);

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
        remainingCrawlTime -= (delta/1000.0f);

        if(remainingCrawlTime <= 0)
        {
            snake.Move(snake.direction);
            remainingCrawlTime = crawlTime;
        }

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

    crawlTime = 0.5;
    remainingCrawlTime = crawlTime;

    snake.direction = direction::right;
    snake.pieces.clear();
    snake.Grow();
    
    apples.clear();
    spikes.clear();

    state = game_state_t::running;
}

void CTG::Snake::Grow()
{
    std::cout << "Grow()!" << std::endl;

    SnakePiece *piece; 
    
    if(pieces.empty())
    {
        piece = InitSnakePiece(nullptr, direction);
        std::cout << "Head: " << piece->bounds.x << ", " << piece->bounds.y << "Size: " << pieces.size() << std::endl;
    }
    else
    {
        SnakePiece *back = pieces.back();
        piece = InitSnakePiece(back, direction);
    }

    pieces.push_back(piece);
}

bool CTG::Snake::CheckDeath()
{
    return false;
}

void CTG::Snake::Move(CTG::direction_t direction)
{
    float dx, dy;

    std::cout << "Move!" << std::endl;

    switch(direction)
    {
        case direction_t::up:
            dx = 0;
            dy = -1;
            break;

        case direction_t::down:
            dx = 0;
            dy = 1;
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

    SnakePiece *head = pieces[0];

    if(pieces.size() == 1)
    {
        head->x_pos_float += 8 * dx;
        head->y_pos_float += 8 * dy;
        head->bounds.x = (int)head->x_pos_float;
        head->bounds.y = (int)head->y_pos_float;
    }
    else
    {
        SnakePiece *tail = pieces.back();
        pieces.pop_back();

        tail->x_pos_float = head->x_pos_float + 8 * dx;
        tail->y_pos_float = head->y_pos_float + 8 * dy;
        tail->bounds.x = tail->x_pos_float;
        tail->bounds.y = tail->y_pos_float;

        pieces.insert(pieces.begin(), tail);
    }   
}

CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece, CTG::direction_t direction)
{
    CTG::SnakePiece *piece = new CTG::SnakePiece;
    piece->sprite = nullptr;


    if(priorPiece == nullptr)
    {
        piece->bounds.x = 640 / 2;
        piece->bounds.y = 480 / 2;
        piece->x_pos_float = piece->bounds.x;
        piece->y_pos_float = piece->bounds.y;
        piece->bounds.w = 16;
        piece->bounds.h = 16;
    }
    else
    {
        float offsetX, offsetY;

        switch(direction)
        {
            case CTG::direction_t::up:
                offsetX = 0;
                offsetY = -1;
                break;

            case CTG::direction_t::down:
                offsetX = 0;
                offsetY = 1;
                break; 

            case CTG::direction_t::left:
                offsetX = 1;
                offsetY = 0;
                break;

            case CTG::direction_t::right:
                offsetX = -1;
                offsetY = 0;
                break;  
        }

        piece->bounds.x = priorPiece->bounds.x + offsetX * priorPiece->bounds.w;
        piece->bounds.y = priorPiece->bounds.y + offsetY * priorPiece->bounds.h;
        piece->bounds.w = priorPiece->bounds.w;
        piece->bounds.h = priorPiece->bounds.h;
        piece->x_pos_float = piece->bounds.x;
        piece->y_pos_float = piece->bounds.y;

        std::cout << "Prev piece: " << priorPiece->bounds.x << "," << priorPiece->bounds.y << "Next piece: " << piece->bounds.x << ", " << piece->bounds.y << std::endl;

    }

    return piece;
}