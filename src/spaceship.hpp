#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include <vector>
class Spaceship
{
    public:
        Spaceship();
        ~Spaceship();

        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireBullet();
        Rectangle GetRect();
        void Reset();
        std::vector<Bullet> bullets;

    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
        Sound bulletSound;

};
