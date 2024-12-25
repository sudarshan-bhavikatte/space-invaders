#pragma once
#include <raylib.h>

class Alien{
    public:
        Alien(int type,Vector2 position);
        static Texture2D images[3];
        Vector2 position;
        int type;
        void Draw();
        void Update(int direction);
        int GetType();
        static void UnloadImages();
        Rectangle GetRect();
};