#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game
{
private:
    Spaceship spaceship;
    void DeleteInactiveBullets();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootBullets();
    void CheckCollisions();
    void GameOver();
    void Reset();
    void InitGame();
    void CheckHighScore();

    std::vector<Obstacle> Obstacles;
    std::vector<Alien> aliens;
    int alienDirection;
    std::vector<Bullet> alienBullets;
    constexpr static float alienFireInterval = 1.0;
    float LastAlienFireTime;
    Mysteryship mysteryship;
    float mysteryshipSpawnInterval;
    float lastSpawnInterval;
    Sound explosoinSound;

public:
    int highScore;
    int lives;
    bool run;
    int score;
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleKey();
    Music music;
};

