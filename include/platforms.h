#pragma once
#include "raylib.h"
#include "raymath.h"
#include "defaults.h"
#include "colors.h"

typedef struct Platform
{
    Vector2 position;
    Vector2 size;
    Color color;
} Platform;

Platform PLATOFRMS[ON_SCREEN_PLATFORM_COUNT];

Platform init_platform(Vector2 position, Vector2 size, Color color)
{
    Platform platform = {
        .position = position,
        .size = size,
        .color = color,
    };
    return platform;
}

Platform get_random_platform(Vector2 size, Vector2 visible_area)
{
    return (Platform){
        .position = (Vector2){
            .x = GetRandomValue(0, visible_area.x-size.x),
            .y = GetRandomValue(0, visible_area.y-size.y),
        },
        .size = size,
        .color = get_random_color(),
    };
}

void fix_overlap(Platform* PA, float player_height)
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        if (fabsf(PA[i].position.y - PA[i+1].position.y) < PA[i].size.y)
        {
            PA[i].position.y -= fmax(PA[i].size.y*2, PA[i+1].size.y*2);
        };
    }
}

void populate_platforms(Platform PA[ON_SCREEN_PLATFORM_COUNT], Vector2 visible_area, Vector2 size, float player_height)
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        PA[i] = get_random_platform(size, visible_area);
    }
    fix_overlap(PA, player_height);
}

void draw_platforms(Platform platform_array[ON_SCREEN_PLATFORM_COUNT])
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(platform_array[i].position, platform_array[i].size, platform_array[i].color);
    }
}
