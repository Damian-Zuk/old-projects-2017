#ifndef player_h
#define player_h

#include "Entity.h"

class Player :public Entity{
private:
    float speed;
public:
    Player(float=0, float=0);
    void Jump();
    void Logic();
    virtual void Update();
    virtual void Render();
};
#endif // player_h
