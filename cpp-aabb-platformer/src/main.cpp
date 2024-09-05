#include "game.h"
#include <cstdlib>
#include <time.h>

int main(int argc, char * argv[]){
    srand(time(0));
    Game * game = new Game(60, true);
    game->initSDL("Test", 1280, 720, false);
    const float delay = (1000 / static_cast<float>(game->fpsCap))/1000;
    while(game->isRunning()){
        game->TotalUpdate();
        if(delay - Game::DeltaT > 0.001f && game->vsync == false){
            SDL_Delay(delay - Game::DeltaT);
        }
    }
    game->Clean();
    return 0;
}
