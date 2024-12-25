#include "spaceship.hpp"

Spaceship::Spaceship()
{
    bulletSound = LoadSound("sounds/laser.ogg");
    image = LoadTexture("graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = (GetScreenHeight() - image.height)- 100;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
    UnloadSound(bulletSound);

}

void Spaceship::Draw(){
    DrawTextureV(image,position,WHITE);
}

void Spaceship::MoveLeft(){
    if(position.x > 25)
    position.x -= GetScreenWidth()/100;
}

void Spaceship::MoveRight(){
    if(position.x < GetScreenWidth() - image.width - 25)
    position.x += GetScreenWidth()/100;
}

void Spaceship::FireBullet(){
    if(GetTime() - lastFireTime >=0.25){
    PlaySound(bulletSound);
    bullets.push_back(Bullet({position.x + image.width/2 - 2,position.y},-6));
    lastFireTime = GetTime();
    }
}

Rectangle Spaceship::GetRect()
{
    return {position.x,position.y,float(image.width),float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = (GetScreenHeight() - image.height)- 100;
    lastFireTime = 0.0;
    bullets.clear();
}
