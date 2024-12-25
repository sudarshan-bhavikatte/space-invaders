#include "bullet.hpp"
#include <iostream>
Bullet::Bullet(Vector2 position , int speed){
    this->position = position;
    this->speed = speed;
    this->active = true;
}


void Bullet::Draw(){
    if(active)
        DrawRectangle(position.x,position.y,4,15,{243,216,43,255});
}

void Bullet::update(){
    position.y += speed;
    if(active){
        if(position.y > GetScreenHeight() - 100 || position.y < 25){
            active = false;
            std::cout << "bullet out of bounds" << std::endl;
        }
    }
}

Rectangle Bullet::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}
