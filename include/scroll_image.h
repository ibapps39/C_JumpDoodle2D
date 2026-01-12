#pragma once
#include "raylib.h"
#include "raymath.h"

// positive speed scrolls down, negative scrolls up
void scroll(Vector2* texture_pos, float texture_speed)
{
    texture_pos->y += texture_speed;
}
