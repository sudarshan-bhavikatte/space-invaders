#include <raylib.h>
#include "game.hpp"
#include <string>
#include <iostream>

std::string FormatNumber(int number,int width){
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
     if (leadingZeros < 0) leadingZeros = 0;
    numberText = std::string(leadingZeros,'0') + numberText;
    return numberText;
}

int main(){
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;
    Color bgColor = {0,0,0,0};
    Color yellow = {243,216,43,255};
    Color red = {255,0,0,255};

    InitWindow(windowWidth + offset ,windowHeight + 2*offset, "hello");
    SetTargetFPS(60); 
    InitAudioDevice();
    Font font = LoadFontEx("graphics/monogram.ttf",64,0,0);
    Texture2D spaceshipImage = LoadTexture("graphics/spaceship.png");
    Game game;
    while(WindowShouldClose() == false){ 
        UpdateMusicStream(game.music);
        game.HandleKey();
        game.Update();
        BeginDrawing();
        ClearBackground(bgColor);
        DrawRectangleRoundedLines({10,10,780,780},0.08f, 20, 2, yellow);
        DrawLineEx({25,730},{775, 730}, 3, yellow);
        if(game.run)
            DrawTextEx(font,"LEVEL 01",{570,740}, 34, 2, yellow);
        else{
            std::string scoreText = FormatNumber(game.highScore,5);
            DrawTextEx(font,scoreText.c_str(),{650,45}, 34, 2, yellow);
            DrawTextEx(font,"GAME OVER",{570,740}, 34, 2, red);
        }
        float x = 50.0;
        for(int i=0;i<game.lives;i++){
            DrawTextureV(spaceshipImage,{x,745},WHITE);
            x += 50;
        }
        DrawTextEx(font,"SCORE",{50,15}, 34, 2, red);
        std::string scoreText = FormatNumber(game.score,5);
        DrawTextEx(font,scoreText.c_str(),{50,45}, 34, 2, red);

        game.Draw();
        EndDrawing();


    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}