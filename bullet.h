#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

class Bullet
{
public:
    Vector2 Pos = { 0 };
    Vector2 Velocity = { 0 };
    float Speed = 750;
    float Lifetime = 0;
    const int Size = 2;

    Bullet(Vector2& playerPos, Vector2& velocityVector);

    bool IsDead();
    void Update();
    void Draw();

protected:
    float ShotAngle = 0;
};

#endif // BULLET_H
