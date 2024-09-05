#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "player.h"
#include "game.h"
#include "InputManager.h"
#include "world.h"


Player::Player(float startX, float startY)
{
    this->xVel = this->speed/Game::fpsCap;
    this->objectRect.w = 40;
    this->objectRect.h = 60;
    this->mass = 450.0f;
    this->speed = 450.0f;
    this->xPos = startX;
    this->yPos = startY;
    this->physics = true;
}

void Player::Update()
{
    if(Game::MapMgr->MapH > 0 && Game::MapMgr->MapW > 0)
    {
        this->Logic();
        Game::CameraMgr->CameraFocus(this);
        this->objectRect.x = this->xPos - Game::CameraMgr->camX;
        this->objectRect.y = this->yPos - Game::CameraMgr->camY;
    }
}

void Player::Jump()
{
    if(this->jumping == false)
        this->yVel = this->mass * 3.5;
}

void Player::Logic()
{
    if(this->moving)  // Przyspieszenie
    {
        float newVel = this->xVel;
        if(newVel > 0.0f)
        {
            if(newVel < this->speed)
                newVel += 4 * this->speed * Game::DeltaT;
            else if(newVel > this->speed)
                newVel = this->speed;
        }
        else if(newVel < 0.0f)
        {
            if(newVel > -this->speed)
                newVel -= 4 * this->speed * Game::DeltaT;
            else if(newVel < -this->speed)
                newVel = -this->speed;
        }
        this->xVel = newVel;
    }
    if((Game::InputMgr->ScanKey(SDL_SCANCODE_A) == false && this->xVel < 0)
        || (Game::InputMgr->ScanKey(SDL_SCANCODE_D) == false && this->xVel > 0))
    {
        this->xVel = 0;
        this->moving = false;
    }
    if(Game::InputMgr->ScanKey(SDL_SCANCODE_D) && !this->moving)
    {
        this->xVel = this->speed/4; // Predkosc poczatkowa
        this->moving = true;
        if(this->yVel > 0.0f) this->yVel *= 0.95f;
        else if(this->yVel < 0.0f) this->yVel *= 1.05f;
    }
    if(Game::InputMgr->ScanKey(SDL_SCANCODE_A) && !this->moving)
    {
        this->xVel = -this->speed/4; // Predkosc poczatkowa
        this->moving = true;
        if(this->yVel > 0.0f) this->yVel *= 0.95f;
        else if(this->yVel < 0.0f) this->yVel *= 1.05f;
    }
    if(Game::InputMgr->ScanKey(SDL_SCANCODE_R))
    {
        this->yPos = 600.0f;
        this->xPos = 50.0f;
    }
    if(Game::InputMgr->ScanKey(SDL_SCANCODE_SPACE))
    {
        this->Jump();
    }
    if(this->physics) World::affectPhysics(this);
}

void Player::Render()
{
    if(Game::MapMgr->MapH > 0 && Game::MapMgr->MapW > 0)
    {
        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Game::renderer, &this->objectRect);
    }
}
