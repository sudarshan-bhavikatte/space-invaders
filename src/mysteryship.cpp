#include "mysteryship.hpp"

Mysteryship::Mysteryship()
{
    image = LoadTexture("graphics/mystery.png");
    alive = false;
}

Mysteryship::~Mysteryship()
{
    UnloadTexture(image);
}

void Mysteryship::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0,1); 

    if(side == 0){
        position.x =25;
        speed = 3;
    } else{
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}


Rectangle Mysteryship::GetRect()
{   
    if(alive)
        return {position.x,position.y,float(image.width),float(image.height)};
    return {position.x,position.y,0,0};
}

void Mysteryship::Update(){
    
    if(alive){
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width - 25|| position.x < 25 ){
            alive = false;
        }
    }
}

void Mysteryship::Draw(){
    if(alive){
        DrawTextureV(image,position,WHITE);
    }
}
