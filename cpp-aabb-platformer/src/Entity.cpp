#include "Entity.h"
#include "game.h"
Entity::Entity()
{
    Game::gameObjects.push_back(this);
}
