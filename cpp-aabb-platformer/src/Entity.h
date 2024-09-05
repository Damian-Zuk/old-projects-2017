#ifndef ENTITY_H
#define ENTITY_H
#include "gameObject.h"


class Entity : public gameObject
{
protected:
    float xVel;
    float yVel;
    float mass;
    bool moving;
    bool jumping;
    bool physics;
public:
    friend class World;
    Entity();
    inline bool getMov(){ return moving; }
    inline bool getJmp(){ return jumping; }
    inline float getXV(){ return xVel; }
    inline float getYV(){ return yVel; }
};
#endif // ENTITY_H
