#include "alien.hpp"

Texture2D Alien::images[3] = {};

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;

    if(images[type - 1].id == 0){

        switch (type)
        {
            case 1:
                images[0]= LoadTexture("graphics/alien_1.png");
                break;
            case 2:
                images[1] = LoadTexture("graphics/alien_2.png");
                break;
            case 3:
                images[2] = LoadTexture("graphics/alien_3.png");
                break;
            
            default:
                images[0]= LoadTexture("graphics/alien_1.png");
                break;
        }
    }
}

void Alien::Draw(){
    DrawTextureV(images[type - 1],position,WHITE);
}

int Alien::GetType(){
    return type;
}


void Alien::UnloadImages(){
    for(int i=0;i<3;i++){
        UnloadTexture(images[i]);
    }
}

Rectangle Alien::GetRect()
{
    return {position.x,position.y,float(images[type - 1].width),float(images[type - 1].height)};
}

void Alien::Update(int direction){
    position.x += direction;
}