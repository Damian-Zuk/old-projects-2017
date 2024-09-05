#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "gameObject.h"
#include <string>

class Background : public gameObject
{
    SDL_Texture *backgroundImage;
    float spdX;
    float spdY;
public:
    Background(int, float, float, std::string);
    virtual void Update();
    virtual void Render();
};
#endif // BACKGROUND_H
