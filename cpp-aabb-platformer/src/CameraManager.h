#ifndef CameraManager_h
#define CameraManager_h
#include "gameObject.h"

class CameraManager{
private:
public:
    SDL_Rect camRect;
    float camX;
    float camY;
    void CameraFocus(gameObject*);
    CameraManager();
    ~CameraManager();
};

#endif // CameraManager_h
