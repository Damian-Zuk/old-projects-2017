#include <iostream>
#include "gameObject.h"
#include "game.h"

gameObject::gameObject(){
    std::cout << "Object: " << this << " created!" << std::endl;
   //Game::gameObjects.push_back(this);
}

gameObject::~gameObject(){

}
