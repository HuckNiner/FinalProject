#include "utils.h"
#include "raylib.h"
#include "raymath.h"

constexpr int TargetSize = 20;

void SetRandomTarget(Vector2& pos)
{
    pos.x = (float)GetRandomValue(TargetSize, GetScreenWidth() - TargetSize);
    pos.y = (float)GetRandomValue(TargetSize, GetScreenHeight() - TargetSize);
}

void KeepPosInBounds(Vector2& pos, float size, Vector2* velocity)
{
    if (pos.x < size)
    {
        if (velocity)
            velocity->x *= -1;
        pos.x = size;
    }

    if (pos.y < size)
    {
        if (velocity)
            velocity->y *= -1;
        pos.y = size;
    }

    if (pos.x > GetScreenWidth() - size)
    {
        if (velocity)
            velocity->x *= -1;
        pos.x = GetScreenWidth() - size;
    }

    if (pos.y > GetScreenHeight() - size)
    {
        if (velocity)
            velocity->y *= -1;
        pos.y = GetScreenHeight() - size;
    }
}
