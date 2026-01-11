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

void parallax(float screen_x, float screen_y, float dy, float dx, float dt)
{
    static bool initialized = false;
    static Color color_x;
    static Color color_y;
    int row_s = screen_y / 10; 
    int col_s = screen_x / 10;

    if (!initialized)
    {
        color_x = get_random_color();
        color_y = get_random_color();
        int same_color = (
            color_x.r == color_y.r &&
            color_x.g == color_y.g &&
            color_x.b == color_y.b
        );
        int similar_color = (
            fabs(color_x.r - color_y.r) < 30 &&
            fabs(color_x.g - color_y.g) < 30 &&
            fabs(color_x.b - color_y.b) < 30
        );
        if (same_color || similar_color)
        {
            color_y = get_random_color();
        }
        initialized = true;
    }
    static float total_dy = 0;
    static float total_dx = 0;
    total_dy -= dy * 0.3;
    total_dx -= dx * 0.3;
    
    float wrap_y = fmodf(total_dy, row_s);
    float wrap_x = fmodf(total_dx, col_s);

    for (size_t row = 0; row < screen_y; row += row_s)
    {
        int offset_r = row - wrap_y;
        DrawLine(0, offset_r, screen_x, offset_r, color_y); // ROW
    }
    for (size_t col = 0; col < screen_x; col += col_s)
    {
        int offset_c = col - wrap_x;
        DrawLine(offset_c, 0, offset_c, screen_y, color_x); // COL
    }
}