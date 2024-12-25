#pragma once
#include <raylib.h>

class Mysteryship
{
private:
    int speed;
    Vector2 position;
    Texture2D image; 
public:
    Mysteryship();
    ~Mysteryship();
    void Update();
    void Draw();
    void Spawn();
    Rectangle GetRect();
    bool alive;
};
