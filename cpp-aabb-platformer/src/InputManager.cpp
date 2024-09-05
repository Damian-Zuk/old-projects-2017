#include "InputManager.h"

InputManager::InputManager(){
}

InputManager::~InputManager(){
}

bool InputManager::ScanKey(SDL_Scancode scan){
    return this->kStates[scan];
}

void InputManager::Update(){
    this->kStates = SDL_GetKeyboardState(NULL);
}
