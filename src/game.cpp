#include <iostream>
#include "game.hpp"
Game::Game()
{   
    Obstacles = CreateObstacles();
    aliens = CreateAliens();
    alienDirection = 1;
    LastAlienFireTime = 0.0;
    mysteryshipSpawnInterval = GetRandomValue(10,20);
    lives = 3;
    run = true;
    score = 0;
    music = LoadMusicStream("sounds/music.ogg");
    PlayMusicStream(music);
    explosoinSound = LoadSound("sounds/explosion.ogg");

    highScore = 0;
}

Game::~Game(){
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosoinSound);
}

void Game::Draw(){
    spaceship.Draw();
    for(auto &bullet:spaceship.bullets){
        bullet.Draw();
    }

    for(auto &obstacle:Obstacles){
        obstacle.Draw();
    }

    for(auto &alein:aliens){
        alein.Draw();
    }

    for(auto &bullet:alienBullets){
        bullet.Draw();
    }

    mysteryship.Draw();

}

void Game::Update(){
    if(run){

        if(GetTime() - lastSpawnInterval > mysteryshipSpawnInterval){
            mysteryship.Spawn();
            lastSpawnInterval = GetTime();
            mysteryshipSpawnInterval = GetRandomValue(10,20);

        }
        for(auto &bullet:spaceship.bullets){
            bullet.update();
        }
        DeleteInactiveBullets();
        AlienShootBullets();
        CheckCollisions();
        for(auto& bullet : alienBullets){
            bullet.update();
        }
        MoveAliens();
        mysteryship.Update();

    }
    else if(IsKeyDown(KEY_ENTER)){
        Reset();
        InitGame();
    }

}

void Game::HandleKey(){
    if(run){

        if(IsKeyDown(KEY_LEFT)){
            spaceship.MoveLeft();
        }
        else if(IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight();
        }
        if(IsKeyDown(KEY_SPACE)){
            spaceship.FireBullet();
        }
    }
}

void Game::DeleteInactiveBullets(){
    for(auto it = spaceship.bullets.begin() ; it != spaceship.bullets.end();){
        if(!it->active){
            it = spaceship.bullets.erase(it);
        }
        else{
            ++it;
        }
    }

    for(auto it = alienBullets.begin() ; it != alienBullets.end();){
        if(!it->active){
            it = alienBullets.erase(it);
        }
        else{
            ++it;
        }
    }
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int i=0;i<5;i++){
        for(int j=0;j<11;j++){
            int alienType;
            float x = 75 + j * 55;
            float y = 110 + i * 55;
            if(i == 0){
                alienType = 3;
            } else if (i < 3){
                alienType = 2;
            } else {
                alienType = 1;
            }            
            aliens.push_back(Alien(alienType,{x,y})); 
        }
    }
    return aliens;
}
std::vector<Obstacle> Game::CreateObstacles(){

    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - 5*obstacleWidth)/6;

    for(int i=0;i<5;i++){
        float offsetx = (i+1)*gap + i*obstacleWidth;
        Obstacles.push_back(Obstacle({offsetx,float(GetScreenHeight() - 200)}));
    }
    return Obstacles;
}


void Game::MoveAliens(){

    for(auto& alien : aliens){
        
        if(alien.position.x + alien.images[alien.type- 1].width + 25> GetScreenWidth()){
            alienDirection = -1;
            MoveDownAliens(4);
        }
        else if(alien.position.x < 25){
            alienDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(alienDirection);
    }
}

void Game::MoveDownAliens(int distance){

    for(auto& alien : aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootBullets()
{
    if(GetTime() - LastAlienFireTime >= alienFireInterval && !aliens.empty()){

        int randomIndex = GetRandomValue(0,aliens.size()-1);
        Alien& alien = aliens[randomIndex];
        alienBullets.push_back(Bullet({alien.position.x + alien.images[alien.type -1].width/2 ,alien.position.y + alien.images[alien.type -1].height}, 6));
        LastAlienFireTime = GetTime();
    }
}

void Game::CheckCollisions()
{
    //Spaceship Bullets

    for(auto& bullet : spaceship.bullets){
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if(CheckCollisionRecs(it->GetRect() , bullet.GetRect())){

                PlaySound(explosoinSound);
                if(it->type == 1){
                    score += 100;
                } else if(it->type == 2){
                    score += 200;
                }else if(it->type == 3){
                    score += 300;
                }
                CheckHighScore();

                it = aliens.erase(it);
                bullet.active = false;
            }
            else{
                it++;
            }
        }

        for(auto &obstacle : Obstacles){
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->GetRect() , bullet.GetRect())){
                    it = obstacle.blocks.erase(it);
                    bullet.active = false;
                }
                else{
                    it++;
                }
            }
            
        }

        if(CheckCollisionRecs(mysteryship.GetRect() , bullet.GetRect())){
            PlaySound(explosoinSound);
            score += 500;
            CheckHighScore();
            mysteryship.alive = false;
            bullet.active = false;
        }
        
    }
    
    //alien bullets

    for(auto& bullet : alienBullets){
        
        if(CheckCollisionRecs(spaceship.GetRect() , bullet.GetRect())){
            bullet.active = false;
            lives--;
            if(lives == 0){
                GameOver();
            }
            std::cout << "spcaeship hit" << std::endl;
        }

        for(auto &obstacle : Obstacles){
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->GetRect() , bullet.GetRect())){
                    it = obstacle.blocks.erase(it);
                    bullet.active = false;
                }
                else{
                    it++;
                }
            }
            
        }
        
    }

    // alien collison with obstacle

    for(auto &alien : aliens){
        for(auto &obstacle : Obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(alien.GetRect(), it->GetRect())){
                    it = obstacle.blocks.erase(it);
                }
                else{
                    it++;
                }
            }
        }

        if(CheckCollisionRecs(alien.GetRect(),spaceship.GetRect())){
            GameOver();
            std::cout << "spaceship hit by alien" << std::endl; 
        }
    }
}

void Game::GameOver()
{
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienBullets.clear();
    Obstacles.clear();
}

void Game::InitGame()
{
    Obstacles = CreateObstacles();
    aliens = CreateAliens();
    alienDirection = 1;
    LastAlienFireTime = 0.0;
    mysteryshipSpawnInterval = GetRandomValue(10,20);
    lives = 3;
    run = true;
    score = 0;
}

void Game::CheckHighScore()
{
    if(score > highScore){
        highScore = score;
    }
}
