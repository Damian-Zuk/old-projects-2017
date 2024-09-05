#ifndef MapManager_h
#define MapManager_h
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class MapManager
{
    bool LoadMap(int, int);
    void ClearMap();
public:
    friend class Game;
    int MapW;
    int MapH;
    MapManager();
    ~MapManager();
};

#endif // MapManager_h
