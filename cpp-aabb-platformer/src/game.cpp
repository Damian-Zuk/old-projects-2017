#include <iomanip>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <fstream>

#include "game.h"
#include "world.h"
#include "player.h"
#include "platform.h"
#include "background.h"

SDL_Renderer * Game::renderer = nullptr;
Player * Game::player = nullptr;
InputManager * Game::InputMgr = new InputManager();
MapManager * Game::MapMgr = new MapManager();
CameraManager * Game::CameraMgr = new CameraManager();
Uint64 lastFrame;
int Game::width;
int Game::height;
int Game::fpsCap;
bool Game::vsync;
float Game::DeltaT;
std::vector <Entity*> Game::gameObjects;
int ttf = TTF_Init();
TTF_Font* Font = TTF_OpenFont("Sans.ttf", 20);
SDL_Color Color = {255, 0, 255, 255};
SDL_Surface* SdebugInfo;
SDL_Texture* debugInfo;
SDL_Rect debug_rect = {10, 10, 300, 800};
Background * tb;

std::string command = "";

Game::Game(int fpsC, bool vS)
{
    this->gameRunning = false;
    Game::fpsCap = fpsC;
    Game::vsync = vS;
}

Game::~Game()
{
    MapMgr->ClearMap();
}

void Game::pDebugInfo(Player * plr)
{
    std::stringstream ss;
    ss << "X: " << plr->getX() << " Y: " << plr->getY() << "\r\n";
    ss << "XV: " << std::setprecision(1) << std::fixed << plr->getXV() << " YV: " << std::setprecision(1) << std::fixed << plr->getYV() << "\r\n";
    ss << "Moving: " << std::boolalpha << plr->getMov() << "\r\n";
    ss << "Jumping: " << std::boolalpha << plr->getJmp() << "\r\n";
    ss << "Update Time: " << std::fixed << std::setprecision(3) << this->updateTime << "\r\n";
    SdebugInfo = TTF_RenderText_Blended_Wrapped(Font, (ss.str()).c_str(), Color, 300);
    debugInfo = SDL_CreateTextureFromSurface(Game::renderer, SdebugInfo);
    SDL_QueryTexture(debugInfo, NULL, NULL, &debug_rect.w, &debug_rect.h);
    SDL_RenderCopy(Game::renderer, debugInfo, NULL, &debug_rect);
    SDL_DestroyTexture(debugInfo);
    SDL_FreeSurface(SdebugInfo);
}

void Game::initSDL(const char * title, int width, int height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        int flags = SDL_WINDOW_SHOWN;
        if(fullscreen) flags = flags | SDL_WINDOW_FULLSCREEN;
        this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(this->window)
        {
            Game::width = width;
            Game::height = height;
            flags = SDL_RENDERER_ACCELERATED;
            if(this->vsync) flags |= SDL_RENDERER_PRESENTVSYNC;
            this->renderer = SDL_CreateRenderer(this->window, -1, flags);
            if(this->renderer)
            {
                this->gameRunning = true;
                Game::MapMgr->LoadMap(2500, 1530);
                new Platform(0,    1500, 2500, 30);
                new Platform(1200, 1300, 200,  10);
                new Platform(1500, 1100, 200,  10);
                new Platform(1200, 900,  200,  10);
                new Platform(1500, 700,  200,  10);
                new Platform(1200, 500,  200,  10);
                new Platform(1500, 300,  200,  10);
                new Platform(1200, 100,  200,  10);
                new Platform(1700, 1370, 600,  130);
                new Platform(1900, 1170, 120,  200);
                new Platform(800,  1400, 400,  10);
                new Platform(900,  1400, 1,    150);
                tb = new Background(0, 0.3f, 0, "assets/tb.png");
            }
        }
    }
}

bool Game::isRunning()
{
    return this->gameRunning;
}

void Game::Clean()
{
    Game::gameObjects.clear();
    std::vector<Entity*>().swap(Game::gameObjects);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    TTF_Quit();
    std::cout << "SDL cleaned!" << std::endl;
}

void Game::hEvents()
{
    while(SDL_PollEvent(&this->event))
    {
        if(this->event.type == SDL_QUIT)
        {
            this->gameRunning = false;
        }
    }
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void Game::commandExecute(std::string com)
{
    std::vector<std::string> commands;
    int temp = 0;
    for(int i = 0; i < com.length(); i++)
    {
        if(com[i] == 32)
        {
            commands.push_back(com.substr(temp, i-temp));
            temp = i;
        }
    }
    switch(str2int(commands.at(0).c_str()))
    {
    case str2int("loadlevel"):
        {
            if(commands.size() > 1)
            {

            }
            break;
        }
    case str2int("createlevel"):
        {
            if(commands.size() > 1)
            {

            }
            break;
        }
    default:
        {
            std::cout << "Unknown command!" << std::endl;
            break;
        }
    }
}

void Game::Update()
{
    if(_kbhit())
    {
        int k = _getch();
        switch(k)
        {
        case 8:
            {
                command = command.substr(0, command.length()-1);
                std::cout << "\b \b";
                break;
            }
        case 13:
            {
                if(command.length() > 0)
                {
                    std::cout << std::endl;
                    commandExecute(command+" ");
                    command = "";
                }
                break;
            }
        default:
            {
                if(k > 31 && k < 126)
                {
                    command += static_cast<char>(k);
                    std::cout << static_cast<char>(k);
                }
                break;
            }
        }
    }
    Game::InputMgr->Update();
    for(auto GameObject : Game::gameObjects)  // aktualizacja wszystkich obiektow
    {
        GameObject->Update();
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    tb->Render();
    for(auto GameObject : Game::gameObjects)  // render wszystkich obiektow
    {
        GameObject->Render();
    }
    if(Game::player != nullptr) this->pDebugInfo(Game::player);
    SDL_RenderPresent(Game::renderer);
    Game::DeltaT = static_cast<float>(SDL_GetPerformanceCounter() - lastFrame) / SDL_GetPerformanceFrequency();
    lastFrame = SDL_GetPerformanceCounter();
}

void Game::TotalUpdate()
{
    clock_t st = clock();
    this->hEvents();
    this->Update();
    this->Render();
    clock_t ed = clock();
    this->updateTime = static_cast<float>(ed - st)/ CLOCKS_PER_SEC;
}

