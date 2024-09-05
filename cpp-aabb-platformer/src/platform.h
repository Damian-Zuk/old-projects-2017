#ifndef platform_h
#define platform_h
#include "Entity.h"
class Platform :public Entity{
public:
    Platform(float, float, int, int);
    ~Platform();
    void Update();
    void Render();
};
#endif // platform_h
