#ifndef inputmanager_h
#define inputmanager_h
#include <SDL2/SDL.h>

class InputManager{
    const Uint8 * kStates;
public:
    bool ScanKey(SDL_Scancode);
    void Update();
    InputManager();
    ~InputManager();
};

#endif // inputmanager_h
