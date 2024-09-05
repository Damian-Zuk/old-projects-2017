#include "CameraManager.h"
#include "game.h"
#include <iostream>
CameraManager::CameraManager(){
    this->camX = 0;
    this->camY = 0;
}

CameraManager::~CameraManager(){

}

void CameraManager::CameraFocus(gameObject * object){
    int newX = this->camX;
    if(this->camX + Game::width * 0.45f > object->getX()) newX = object->getX() - Game::width * 0.45f;
    else if(this->camX + Game::width * 0.55f < object->getX()) newX = object->getX() - Game::width * 0.55f;
    if(newX > Game::MapMgr->MapW - Game::width) newX = Game::MapMgr->MapW - Game::width;
    else if(newX < 0.0f) newX = 0.0f;
    this->camX = newX;
    int newY = this->camY;
    if(this->camY + Game::height * 0.3f > object->getY()) newY = object->getY() - Game::height * 0.3f;
    else if(this->camY + Game::height * 0.7f < object->getY()) newY = object->getY() - Game::height * 0.7f;
    if(newY > Game::MapMgr->MapH - Game::height) newY = Game::MapMgr->MapH - Game::height;
    else if(newY < 0.0f) newY = 0.0f;
    this->camY = newY;
}
