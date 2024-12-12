#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"

void SetRandomTarget(Vector2& pos);
void KeepPosInBounds(Vector2& pos, float size, Vector2* velocity = nullptr);

#endif // UTILS_H
