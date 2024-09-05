#include "world.h"
#include "helper.h"
#include "game.h"
#include <iostream>
#include <time.h>

float World::gravity = 9.8f;

void World::affectPhysics(Entity * object)
{
    float newPos;
    float Stop;
    //X
    Stop = World::collisionOnX(object);
    newPos = object->xPos + object->xVel * Game::DeltaT;
    if(object->xVel > 0.0f && newPos+object->objectRect.w >= Stop)  // Kolizja prawy bok
    {
        newPos = Stop - object->objectRect.w;
        object->xVel = 0.0f;
    }
    else if(object->xVel < 0.0f && newPos <= Stop)   // Kolizja lewy bok
    {
        newPos = Stop;
        object->xVel = 0.0f;
    }
    if(object->xPos - newPos == 0) object->moving = false;
    object->xPos = newPos;
    //Y
    object->yVel -= World::gravity * object->mass * Game::DeltaT;
    if(object->yVel < -1500.0f) object->yVel = -1500.0f;
    Stop = World::collisionOnY(object);
    newPos = object->yPos - object->yVel * Game::DeltaT;
    if(object->yVel < 0.0f && newPos + object->objectRect.h >= Stop)  // Kolizja dól
    {
        object->jumping = false;
        object->yVel = 0.0f;
        newPos = Stop-object->objectRect.h;
    }
    else if(object->yVel > 0.0f && newPos <= Stop)   // Kolizja góra
    {
        object->jumping = true;
        object->yVel = 0.0f;
        newPos = Stop;
    }
    else object->jumping = true;  // Brak kolizji
    object->yPos = newPos;
}
float World::collisionOnY(Entity * object)
{
    bool temp = true;
    float first = object->yPos+object->objectRect.h;
    if(object->yVel < 0.0f) first = Game::MapMgr->MapH;
    else if(object->yVel > 0.0f) first = 0.0f;
    for(auto GameObject: Game::gameObjects)
    {
        if(GameObject != object)
        {
            if(object->xPos+object->objectRect.w > GameObject->xPos
                    && object->xPos < GameObject->xPos + GameObject->objectRect.w)
            {
                if(object->yVel < 0.0f)
                {
                    if(object->yPos <= GameObject->yPos)
                    {
                        if(temp)
                        {
                            first = GameObject->yPos;
                            temp = false;
                        }
                        else if(GameObject->yPos < first)
                            first = GameObject->yPos;
                    }
                }
                else if(object->yVel > 0.0f)
                {
                    if(object->yPos >= GameObject->yPos)
                    {
                        if(temp)
                        {
                            first = GameObject->yPos + GameObject->objectRect.h;
                            temp = false;
                        }
                        else if(GameObject->yPos + GameObject->objectRect.h > first)
                            first = GameObject->yPos + GameObject->objectRect.h;
                    }
                }
            }
        }
    }
    return first;
}

float World::collisionOnX(Entity * object)
{
    bool temp = true;
    float first = object->xPos+object->objectRect.w;
    if(object->xVel > 0.0f) first = Game::MapMgr->MapW;
    else if(object->xVel < 0.0f) first = 0.0f;
    for(auto GameObject : Game::gameObjects)
    {
        if(GameObject != object)
        {
            if(object->yPos+object->objectRect.h > GameObject->yPos
                    && object->yPos < GameObject->yPos + GameObject->objectRect.h)
            {
                if(object->xVel > 0.0f)
                {
                    if(object->xPos + object->objectRect.w <= GameObject->xPos)
                    {
                        if(temp)
                        {
                            first = GameObject->xPos;
                            temp = false;
                        }
                        else if(GameObject->xPos < first)
                            first = GameObject->xPos;
                    }
                }
                else if(object->xVel < 0.0f)
                {
                    if(object->xPos >= GameObject->xPos + GameObject->objectRect.w)
                    {
                        if(temp)
                        {
                            first = GameObject->xPos + GameObject->objectRect.w;
                            temp = false;
                        }
                        else if(GameObject->xPos + GameObject->objectRect.w > first)
                            first = GameObject->xPos + GameObject->objectRect.w;
                    }
                }
            }
        }
    }
    return first;
}
