#include "background.h"
#include "game.h"
#include <fstream>

Background::Background(int z, float sx, float sy, std::string file)
{
    SDL_Surface * bs = IMG_Load(file.c_str());
    this->backgroundImage = SDL_CreateTextureFromSurface(Game::renderer, bs);
    SDL_FreeSurface(bs);
    this->spdX = sx;
    this->spdY = sy;
    this->xPos = 0;
    this->yPos = 0;
    this->zIndex = z;
    this->objectRect.x = 0;
    this->objectRect.y = 0;
    this->objectRect.w = Game::width;
    this->objectRect.h = Game::height;
}

void Background::Render()
{
    float nX = this->xPos - Game::CameraMgr->camX * this->spdX;
    float nY = this->yPos - Game::CameraMgr->camY * this->spdY;
    this->objectRect.x = nX;
    this->objectRect.y = nY;
    if(nX < 0){
        SDL_Rect second = {this->objectRect.w + nX, nY, this->objectRect.w, this->objectRect.h};
        SDL_RenderCopy(Game::renderer, this->backgroundImage, NULL, &second);
    }
    SDL_RenderCopy(Game::renderer, this->backgroundImage, NULL, &this->objectRect);
}

void Background::Update()
{

}
