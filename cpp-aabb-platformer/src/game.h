#ifndef game_h
#define game_h
#include "InputManager.h"
#include "MapManager.h"
#include "gameObject.h"
#include "player.h"
#include "CameraManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

class Game{
private:
    SDL_Window * window;
    SDL_Event event;
    const char * title;
    bool fullscreen;
    bool gameRunning;
    float updateTime;
    void hEvents();
    void Update();
    void Render();
    void pDebugInfo(Player*);
    void commandExecute(std::string);
public:
    static Player * player;
    static std::vector <Entity*> gameObjects;
    static int width;
    static int height;
    static int fpsCap;
    static bool vsync;
    static SDL_Renderer * renderer;
    static InputManager * InputMgr;
    static MapManager * MapMgr;
    static CameraManager * CameraMgr;
    static float DeltaT;
    bool isRunning();
    void initSDL(const char *, int, int, bool);
    void Clean();
    void TotalUpdate();
    Game(int=60, bool=true);
    ~Game();
};

#endif // game_h
