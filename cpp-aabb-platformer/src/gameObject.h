#ifndef gameobject_h
#define gameobject_h
#include <SDL2/SDL.h>

class gameObject{
protected:
    float xPos;
    float yPos;
    float zIndex;
    SDL_Rect objectRect;
public:
    friend class World;
    gameObject();
    ~gameObject();
    virtual void Update() = 0;
    virtual void Render() = 0;
    inline int getX(){ return static_cast<int>(xPos); }
    inline int getY(){ return static_cast<int>(yPos); }
};

#endif // gameobject_h
