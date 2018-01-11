#include <iostream>
#include <vector>
#include "Snake.hpp"

CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece=nullptr);

void CTG::Snake::Grow()
{
    std::cout << "Grow()!" << std::endl;

    SnakePiece *piece; 
    
    if(pieces.empty())
    {
        piece = InitSnakePiece();
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
        head->x_pos_float += 16 * dx;
        head->y_pos_float += 16 * dy;
        head->bounds.x = (int)head->x_pos_float;
        head->bounds.y = (int)head->y_pos_float;
    }
    else
    {
        SnakePiece *tail = pieces.back();
        pieces.pop_back();

        tail->x_pos_float = head->x_pos_float + 16 * dx;
        tail->y_pos_float = head->y_pos_float + 16 * dy;
        tail->bounds.x = tail->x_pos_float;
        tail->bounds.y = tail->y_pos_float;

        pieces.insert(pieces.begin(), tail);
    }   
}

CTG::SnakePiece * InitSnakePiece(CTG::SnakePiece *priorPiece)
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
        piece->bounds.x = priorPiece->bounds.x;
        piece->bounds.y = priorPiece->bounds.y;
        piece->bounds.w = priorPiece->bounds.w;
        piece->bounds.h = priorPiece->bounds.h;
        piece->x_pos_float = piece->bounds.x;
        piece->y_pos_float = piece->bounds.y;

        std::cout << "Prev piece: " << priorPiece->bounds.x << "," << priorPiece->bounds.y << "Next piece: " << piece->bounds.x << ", " << piece->bounds.y << std::endl;
    }

    return piece;
}