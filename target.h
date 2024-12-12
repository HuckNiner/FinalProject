#ifndef TARGET_H
#define TARGET_H

#include "raylib.h"

class Target
{
public:
    Vector2 Pos = { 0 };
    Vector2 Velocity = { 0 };
    float Speed = 50;
    float Lifetime = 0;
    float Size = 1;

    Target();

    void Reset();
    void Update();
    bool Hit(Vector2& shot, float size);
    void Draw();
};

#endif // TARGET_H
