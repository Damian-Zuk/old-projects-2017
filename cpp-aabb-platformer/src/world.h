#ifndef world_h
#define world_h
#include "Entity.h"

class World{
public:
    static float collisionOnY(Entity*);
    static float collisionOnX(Entity*);
    static float gravity;
    static void affectPhysics(Entity*);
};

#endif // world_h
