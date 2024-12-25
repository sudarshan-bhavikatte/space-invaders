#include <raylib.h>

class Bullet
{
private:
    int speed;
    Vector2 position;
public:
    Bullet(Vector2 position,int speed);
    void Draw();
    void update();
    Rectangle GetRect();
    bool active;
};

