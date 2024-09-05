#include "MapManager.h"
#include "game.h"

MapManager::MapManager(){

}

MapManager::~MapManager(){

}


bool MapManager::LoadMap(int w, int h){
    this->MapW = w;
    this->MapH = h;
    Game::player = new Player(500, 1000);
    return true;
}

void MapManager::ClearMap()
{
    std::vector<Entity*> empty;
    Game::gameObjects.clear();
    Game::gameObjects.swap(empty);
}
