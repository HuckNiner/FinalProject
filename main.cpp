#include "raylib.h"
#include "raymath.h"
#include "utils.h"
#include "target.h"
#include "bullet.h"

#include <cmath>
#include <list>
#include <vector>
#include <string>

constexpr float RefireTime = 0.25f;

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 800, "Shooter Sample");
    SetTargetFPS(144);

    Vector2 PlayerPos = { 600, 400 };
    float PlayerAngle = -90;
    float AimAngle = 0;

    Rectangle screenRect = Rectangle{ 0, 0 ,(float)GetScreenWidth(), (float)GetScreenHeight() };

    bool wantFire = false;
    float reloadTime = -RefireTime;

    std::list<Bullet> bullets;
    std::vector<Target> targets;

    for (int i = 0; i < 10; i++)
    {
        targets.emplace_back(Target());
    }

    int score = 0;
    int lives = 3;
    bool gameOn = true;

    while (!WindowShouldClose())
    {
        Vector2 aimVector = Vector2Normalize(Vector2Subtract(GetMousePosition(), PlayerPos));
        Vector2 movementVector = Vector2{ cosf(PlayerAngle * DEG2RAD), sinf(PlayerAngle * DEG2RAD) };

        if (gameOn)
        {
            float moveSpeed = 200 * GetFrameTime();
            float turnSpeed = 180 * GetFrameTime();

            if (IsKeyDown(KEY_A))
                PlayerAngle -= turnSpeed;
            if (IsKeyDown(KEY_D))
                PlayerAngle += turnSpeed;

            movementVector = Vector2{ cosf(PlayerAngle * DEG2RAD), sinf(PlayerAngle * DEG2RAD) };

            if (IsKeyDown(KEY_W))
                PlayerPos = Vector2Add(PlayerPos, Vector2Scale(movementVector, moveSpeed));
            if (IsKeyDown(KEY_S))
                PlayerPos = Vector2Add(PlayerPos, Vector2Scale(movementVector, -moveSpeed));

            KeepPosInBounds(PlayerPos, 30);

            aimVector = Vector2Normalize(Vector2Subtract(GetMousePosition(), PlayerPos));
            if (Vector2LengthSqr(aimVector) > 0)
                AimAngle = atan2f(aimVector.y, aimVector.x) * RAD2DEG;

            aimVector.x = cosf(AimAngle * DEG2RAD);
            aimVector.y = sinf(AimAngle * DEG2RAD);
        }
        else
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameOn = true;
                score = 0;
                lives = 3;
                SetRandomTarget(PlayerPos);

                while (targets.size() > 10)
                    targets.erase(targets.begin());
            }
        }

        for (auto& target : targets)
        {
            target.Update();

            if (target.Hit(PlayerPos, 30))
            {
                lives--;
                SetRandomTarget(PlayerPos);
                if (lives <= 0)
                {
                    gameOn = false;
                }
            }
        }

        if (gameOn)
        {
            reloadTime -= GetFrameTime();
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && reloadTime <= 0)
            {
                wantFire = false;
                reloadTime = RefireTime;
                bullets.emplace_back(Bullet(PlayerPos, aimVector));
            }
        }

        for (auto itr = bullets.begin(); itr != bullets.end();)
        {
            itr->Update();
            if (itr->IsDead() || !gameOn)
            {
                itr = bullets.erase(itr);
            }
            else
            {
                for (auto& target : targets)
                {
                    if (target.Hit(itr->Pos, itr->Size * 2.0f))
                    {
                        itr->Lifetime = 0;
                        score++;

                        if (score % 10 == 0)
                            targets.emplace_back(Target());
                    }
                }
                itr++;
            }
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);

        for (auto& target : targets)
            target.Draw();

        for (auto& bullet : bullets)
            bullet.Draw();

        if (gameOn)
        {
            DrawRectanglePro(Rectangle{ PlayerPos.x, PlayerPos.y, 40, 30 }, Vector2{ 20, 15 }, PlayerAngle, DARKGRAY);
            DrawCircle((int)(PlayerPos.x + movementVector.x * 15), (int)(PlayerPos.y + movementVector.y * 15), 7, GRAY);
            DrawCircle((int)PlayerPos.x, (int)PlayerPos.y, 10, BLUE);

            Rectangle aimRectangle = { PlayerPos.x, PlayerPos.y, 26, 4 };
            DrawRectanglePro(aimRectangle, Vector2{ -5, 2 }, AimAngle, DARKBLUE);

            DrawText(TextFormat("Score %d Lives %d", score, lives), 0, 0, 20, RAYWHITE);
        }
        else
        {
            std::string message = "Game Over, Click to Restart";
            int textSize = MeasureText(message.c_str(), 20);
            DrawText(message.c_str(), GetScreenWidth() / 2 - textSize / 2, 400, 20, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
