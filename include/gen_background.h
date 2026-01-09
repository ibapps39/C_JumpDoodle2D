#pragma once

#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "defaults.h"
#include "colors.h"


void genereate_random_background(float screen_x, float screen_y, Vector2 *player_pos)
{
    static bool initialized = false;
    static Color color_x;
    static Color color_y;

    if (!initialized)
    {
        color_x = get_random_color();
        color_y = get_random_color();
        if (color_x.r == color_y.r &&
            color_x.g == color_y.g &&
            color_x.b == color_y.b)
        {
            color_y = get_random_color();
        }
        initialized = true;
    }

    for (size_t y = 0; y < screen_y; y += screen_y / 10)
    {
        DrawLine(0, y, screen_x, y, color_y);
        for (size_t x = 0; x < screen_x; x += screen_x / 10)
        {
            // Generate a random but bright and neon looking Color
            DrawLine(x, 0, x, screen_y, color_x);
        }
    }
}