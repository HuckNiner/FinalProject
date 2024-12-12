#include "bullet.h"
#include "raylib.h"
#include "raymath.h"

Bullet::Bullet(Vector2& playerPos, Vector2& velocityVector)
{
    Velocity = velocityVector;

    if (Vector2LengthSqr(Velocity) == 0)
    {
        Lifetime = -1;
        return;
    }

    Pos = Vector2Add(playerPos, Vector2Scale(Velocity, 10));
    Lifetime = 2;
    ShotAngle = atan2f(Velocity.y, Velocity.x) * RAD2DEG;
}

bool Bullet::IsDead()
{
    return Lifetime <= 0;
}

void Bullet::Update()
{
    Lifetime -= GetFrameTime();
    if (Lifetime <= 0)
        return;

    Pos = Vector2Add(Pos, Vector2Scale(Velocity, Speed * GetFrameTime()));

    if (Pos.x < -Size || Pos.y < -Size || Pos.x > GetScreenWidth() + Size || Pos.y > GetScreenHeight() + Size)
    {
        Lifetime = -1;
        return;
    }
}

void Bullet::Draw()
{
    Rectangle rect = { Pos.x, Pos.y, Size * 6.0f, Size * 2.0f };
    Vector2 center = { Size * 3.0f, (float)Size };
    DrawRectanglePro(rect, center, ShotAngle, RED);
}
