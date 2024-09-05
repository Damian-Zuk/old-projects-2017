#include "platform.h"
#include "game.h"
#include "world.h"

Platform::Platform(float x, float y, int width, int height){
    this->xPos = x;
    this->yPos = y;
    this->objectRect.w = width;
    this->objectRect.h = height;
    this->physics = false;
}

Platform::~Platform(){

}

void Platform::Update(){
    this->objectRect.x = this->xPos - Game::CameraMgr->camX;
    this->objectRect.y = this->yPos - Game::CameraMgr->camY;
    if(this->physics) World::affectPhysics(this);
}

void Platform::Render(){
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &this->objectRect);
}
