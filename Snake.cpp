#include <iostream>
#include <vector>
#include <cmath>
#include "Snake.hpp"
#include "SDLHelpers.hpp"

namespace CTG
{
const int SEGMENT_SIZE = 16;
}

void DirectionToPoint(SDL_Point &, CTG::direction_t &);

void CTG::Snake::Grow()
{
    //std::cout << "Grow()!" << std::endl;

    SnakePiece *piece = new CTG::SnakePiece;
    piece->sprite = nullptr;

    SDL_Point pieceTargetLocation;

    if (pieces.empty())
    {
        piece->bounds.x = 640 / 2;
        piece->bounds.y = 480 / 2;
        piece->x_pos_float = piece->bounds.x;
        piece->y_pos_float = piece->bounds.y;
        piece->bounds.w = SEGMENT_SIZE;
        piece->bounds.h = SEGMENT_SIZE;

        SDL_Point d;
        DirectionToPoint(d, direction);

        pieceTargetLocation.x = piece->bounds.x + d.x * SEGMENT_SIZE;
        pieceTargetLocation.y = piece->bounds.y + d.y * SEGMENT_SIZE;
    }
    else
    {
        SnakePiece *back = pieces.back();

        piece->bounds.x = back->bounds.x;
        piece->bounds.y = back->bounds.y;
        piece->bounds.w = back->bounds.w;
        piece->bounds.h = back->bounds.h;
        piece->x_pos_float = piece->bounds.x;
        piece->y_pos_float = piece->bounds.y;

        pieceTargetLocation.x = targetLocations[pieces.size() - 1].x;
        pieceTargetLocation.y = targetLocations[pieces.size() - 1].y;

        pieceTargetLocation.x = -1;
        pieceTargetLocation.y = -1;
    }

    pieces.push_back(piece);
    targetLocations.push_back(pieceTargetLocation);
}

void CTG::Snake::Update(int delta)
{
    //std::cout << "Update: " << delta << std::endl;
    float dt = delta / 1000.0f;

    SDL_Point d;
    DirectionToPoint(d, direction);

    for (int i = 0; i < pieces.size(); i++)
    {
        SnakePiece *piece = pieces[i];
        SDL_Point target = targetLocations[i];

        if (target.x == -1 || target.y == -1)
        {
            std::cout << "Piece: " << i << " not updating..." << std::endl;
            continue;
        }

        float xDiff = target.x - piece->x_pos_float;
        float yDiff = target.y - piece->y_pos_float;

        float xMul = xDiff < 0 ? -1 : 1;
        float yMul = yDiff < 0 ? -1 : 1;

        if (i == 0)
        {
            SDL_Point curLoc;
            curLoc.x = piece->bounds.x;
            curLoc.y = piece->bounds.y;

            double dist = SDL_Point_Distance(curLoc, target);

            if(abs(xDiff) < 0.1 && abs(yDiff) < 0.1)
            {
                UpdateTargetLocations();
                target = targetLocations[i];
                /* std::cout << "Head needs update: (" << piece->x_pos_float << ", " << piece->y_pos_float << ") "
                      << " target: (" << target.x << "," << target.y << ")" << std::endl; */
            }
        }

        float oldX = piece->x_pos_float;
        float oldY = piece->y_pos_float;

        //piece->x_pos_float += xMul * velocity * dt;
        //piece->y_pos_float += yMul * velocity * dt;

        piece->x_pos_float += xMul * velocity * dt;
        piece->y_pos_float += yMul * velocity * dt;

        piece->bounds.x = round(piece->x_pos_float);
        piece->bounds.y = round(piece->y_pos_float);

        if(i == 0)
            std::cout << "Piece: " << i << ", old (" << oldX << "," << oldY << "), now: (" << piece->bounds.x << ", " << piece->bounds.y << ")"
                  << " target: (" << target.x << "," << target.y << ")" << std::endl; 
    }
}

bool CTG::Snake::CheckDeath()
{
    return false;
}

void CTG::Snake::Move(CTG::direction_t direction)
{
    SDL_Point d;
    DirectionToPoint(d, direction);

    SnakePiece *head = pieces[0];

    if (pieces.size() == 1)
    {
        head->x_pos_float += SEGMENT_SIZE * d.x;
        head->y_pos_float += SEGMENT_SIZE * d.y;
        head->bounds.x = (int)head->x_pos_float;
        head->bounds.y = (int)head->y_pos_float;
    }
    else
    {
        SnakePiece *tail = pieces.back();
        pieces.pop_back();

        tail->x_pos_float = head->x_pos_float + SEGMENT_SIZE * d.x;
        tail->y_pos_float = head->y_pos_float + SEGMENT_SIZE * d.y;
        tail->bounds.x = tail->x_pos_float;
        tail->bounds.y = tail->y_pos_float;

        pieces.insert(pieces.begin(), tail);
    }
}

void CTG::Snake::UpdateTargetLocations()
{
    for (int i = pieces.size(); i >= 0; i--)
    {
        if (i == 0)
        {
            SDL_Point d;
            DirectionToPoint(d, direction);

            SDL_Point tLoc;
            tLoc.x = SEGMENT_SIZE * (pieces[i]->bounds.x/SEGMENT_SIZE) + (d.x * SEGMENT_SIZE);
            tLoc.y = SEGMENT_SIZE * (pieces[i]->bounds.y/SEGMENT_SIZE) + (d.y * SEGMENT_SIZE);
            targetLocations[i] = tLoc;

            std::cout << "Set head target location to: " << targetLocations[i].x << "," << targetLocations[i].y << ", tLoc:" << tLoc.x << ", " << tLoc.y << ", direction: " << direction << ", dx: " << d.x << ", dy: " << d.y << std::endl;
        }
        else
        {
            SnakePiece *prev = pieces[i - 1];
            targetLocations[i] = targetLocations[i - 1];
        }
    }
}

void DirectionToPoint(SDL_Point &pt, CTG::direction_t &dir)
{
    switch (dir)
    {
    case CTG::direction_t::up:
        pt.x = 0;
        pt.y = -1;
        break;

    case CTG::direction_t::down:
        pt.x = 0;
        pt.y = 1;
        break;

    case CTG::direction_t::left:
        pt.x = -1;
        pt.y = 0;
        break;

    case CTG::direction_t::right:
        pt.x = 1;
        pt.y = 0;
        break;
    }
}