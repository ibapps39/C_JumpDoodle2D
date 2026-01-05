#pragma once

#include "raylib.h"
#include "raymath.h"
#include "defaults.h"

#define NEON_GREEN (Color){.r = 0, .g = 255, .b = 0, .a = 255}
#define NEON_BLUE (Color){.r = 0, .g = 0, .b = 255, .a = 255}
#define NEON_RED (Color){.r = 255, .g = 0, .b = 0, .a = 255}
#define NEON_YELLOW (Color){.r = 255, .g = 255, .b = 0, .a = 255}
#define NEON_PINK (Color){.r = 255, .g = 0, .b = 255, .a = 255}
#define NEON_PURPLE (Color){.r = 255, .g = 0, .b = 255, .a = 255}

typedef enum neon_colors
{
    green_n,
    blue_n,
    red_n,
    yellow_n,
    pink_n,
    purple_n
} neon_colors;

Color get_neon_color(neon_colors color)
{
    switch (color)
    {
    case green_n:
        return NEON_GREEN;
    case blue_n:
        return NEON_BLUE;
    case red_n:
        return NEON_RED;
    case yellow_n:
        return NEON_YELLOW;
    case pink_n:
        return NEON_PINK;
    case purple_n:
        return NEON_PURPLE;
    default:
        return NEON_GREEN;
    }
}

Color get_random_color()
{
    return get_neon_color((neon_colors)(GetRandomValue(0, 6)));
}