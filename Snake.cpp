#include <iostream>
#include <vector>
#include <cmath>
#include "Snake.hpp"
#include "Scene.hpp"
#include "SDLHelpers.hpp"

namespace CTG
{
const int SEGMENT_SIZE = 20;
}

void DirectionToPoint(SDL_Point &, direction_t &);

void CTG::Snake::Grow()
{
    //std::cout << "Grow()!" << std::endl;

    SnakePiece *piece = new CTG::SnakePiece;
    piece->sprite = nullptr;

    target_location *ptLocation = new target_location;

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

        ptLocation->from_x = piece->bounds.x;
        ptLocation->from_y = piece->bounds.y;
        ptLocation->to_x = piece->bounds.x + d.x * SEGMENT_SIZE;
        ptLocation->to_y = piece->bounds.y + d.y * SEGMENT_SIZE;
        ptLocation->current_time = 0;
        ptLocation->max_time = 1000;

        /* std::cout << "targetLoc from: (" << ptLocation->from_x
                  << ", " << ptLocation->from_y << ") to ("
                  << ptLocation->to_x << ", " << ptLocation->to_y << ")" << std::endl; */
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

        ptLocation->from_x = -1;
        ptLocation->from_y = -1;
        ptLocation->to_x = -1;
        ptLocation->to_y = -1;
    }

    pieces.push_back(piece);
    targetLocations.push_back(ptLocation);
}

void CTG::Snake::Update(int delta)
{
    //std::cout << "Update: " << delta << std::endl;

    SDL_Point d;
    DirectionToPoint(d, direction);

    for (int i = 0; i < pieces.size(); i++)
    {
        SnakePiece *piece = pieces[i];

        if (targetLocations[i]->to_x == -1 || targetLocations[i]->to_y == -1)
        {
            //std::cout << "Piece: " << i << " not updating..." << std::endl;
            continue;
        }

        targetLocations[i]->current_time =
            std::min(targetLocations[i]->current_time + (velocity * delta),
                     targetLocations[i]->max_time);

        float t = targetLocations[i]->current_time / targetLocations[i]->max_time;

        float oldX = piece->x_pos_float;
        float oldY = piece->y_pos_float;

        piece->x_pos_float = SDL_Lerp(targetLocations[i]->from_x, targetLocations[i]->to_x, t);
        piece->y_pos_float = SDL_Lerp(targetLocations[i]->from_y, targetLocations[i]->to_y, t);

        piece->bounds.x = round(piece->x_pos_float);
        piece->bounds.y = round(piece->y_pos_float);

        /* std::cout << "Piece: " << i << " from (" << oldX << ", " << oldY
            << ") to (" << piece->x_pos_float << ", " << piece ->y_pos_float << ") "
                << " target: (" << targetLocations[i].to_x << ", " << targetLocations[i].to_y
                << ") ct: " << targetLocations[i].current_time << ", mt: " << targetLocations[i].max_time << std::endl; */

        if (i == 0 && t >= 1)
        {
            UpdateTargetLocations();
        }
    }
}

void CTG::Snake::Move(direction_t direction)
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
    for (int i = pieces.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            SnakePiece *piece = pieces[i];

            SDL_Point d;
            DirectionToPoint(d, direction);

            targetLocations[i]->from_x = piece->bounds.x;
            targetLocations[i]->from_y = piece->bounds.y;
            targetLocations[i]->to_x = piece->bounds.x + (d.x * SEGMENT_SIZE);
            targetLocations[i]->to_y = piece->bounds.y + (d.y * SEGMENT_SIZE);
            ;

            /* std::cout << "Updated. Current: (" << targetLocations[i].from_x << ", " << targetLocations[i].to_y 
                << ", Set head target location to: " << targetLocations[i].to_x << "," << targetLocations[i].to_y 
                << ", direction: " << direction << ", dx: " << d.x << ", dy: " << d.y << std::endl; */
        }
        else
        {
            //std::cout << "i: " << i << std::endl;
            //std::cout << "pieces.size(): " << pieces.size() << std::endl;
            //std::cout << "targetLocations.size(): " << targetLocations.size() << std::endl;

            SnakePiece *prev = pieces[i - 1];

            targetLocations[i]->from_x = targetLocations[i - 1]->from_x;
            targetLocations[i]->from_y = targetLocations[i - 1]->from_y;
            targetLocations[i]->to_x = targetLocations[i - 1]->to_x;
            targetLocations[i]->to_y = targetLocations[i - 1]->to_y;
        }

        targetLocations[i]->current_time = 0.0f;
        targetLocations[i]->max_time = 1000.0f;
    }
}

bool CTG::Snake::CheckCollision(SDL_Rect &r, bool includeHead)
{

    for (int i = includeHead ? 0 : 1; i < pieces.size(); i++)
    {
        SDL_Rect ir;
        SnakePiece *p = pieces[i];
        if (SDL_IntersectRect(&r, &p->bounds, &ir) == SDL_TRUE)
        {
            return true;
        }
    }

    return false;
}

bool CTG::Snake::CheckDeath()
{
    SnakePiece *head = pieces[0];

    /* We've hit the walls. Ouch! */
    if (head->bounds.x > CTG::Scene::sceneWidth 
        || head->bounds.y > CTG::Scene::sceneHeight 
        || head->bounds.x <= 0 
        || head->bounds.y <= 0)
    {
        return true;
    }
    else if (pieces.size() > 1)
    {
        /* Check if a multi-segmented snake
            has bitten himself. */

        SDL_Rect iRect;
        int intersectAreaThreshold = 250;

        for (int i = 1; i < pieces.size(); i++)
        {
            if(targetLocations[i]->to_x == -1
                || targetLocations[i]->to_x == -1)
            {
                continue;
            }

            SnakePiece *other = pieces[i];
            SDL_bool result = SDL_IntersectRect(&head->bounds, &other->bounds, &iRect);

            if (result == SDL_TRUE)
            {
                int intersect = iRect.w * iRect.h;

                if (intersect > intersectAreaThreshold)
                {
                    //std::cout << "Intersect: " << intersect << ", dead!";
                    return true;
                }
                //std::cout << i << " intersection: w: " << iRect.w << ", h: " << iRect.h << std::endl;
            }
        }
    }

    return false;
}

void DirectionToPoint(SDL_Point &pt, direction_t &dir)
{
    switch (dir)
    {
    case up:
        pt.x = 0;
        pt.y = -1;
        break;

    case down:
        pt.x = 0;
        pt.y = 1;
        break;

    case left:
        pt.x = -1;
        pt.y = 0;
        break;

    case right:
        pt.x = 1;
        pt.y = 0;
        break;
    }
}