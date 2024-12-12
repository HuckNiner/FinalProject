#include "target.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

constexpr int TargetSize = 20;

Target::Target()
{
    Reset();
}

void Target::Reset()
{
    SetRandomTarget(Pos);
    Velocity.x = GetRandomValue(-1000, 1000) / 1000.0f;
    Velocity.y = GetRandomValue(-1000, 1000) / 1000.0f;
    Velocity = Vector2Normalize(Velocity);

    Lifetime = 0;
    Size = 1;
    Speed = (float)GetRandomValue(50, 150);
}

void Target::Update()
{
    Lifetime += GetFrameTime();

    if (Lifetime < 1)
        Size = 1 + (Lifetime / 1.5f) * (TargetSize - 1);
    else
        Size = TargetSize;

    Pos = Vector2Add(Pos, Vector2Scale(Velocity, Speed * GetFrameTime()));

    KeepPosInBounds(Pos, Size, &Velocity);
}

bool Target::Hit(Vector2& shot, float size)
{
    if (CheckCollisionCircles(Pos, Size, shot, size))
    {
        Reset();
        return true;
    }

    return false;
}

void Target::Draw()
{
    DrawCircle((int)Pos.x, (int)Pos.y, Size, RED);
    DrawCircle((int)Pos.x, (int)Pos.y, Size * 0.75f, WHITE);
    DrawCircle((int)Pos.x, (int)Pos.y, Size * 0.5f, RED);
    DrawCircle((int)Pos.x, (int)Pos.y, Size * 0.25f, WHITE);
}
