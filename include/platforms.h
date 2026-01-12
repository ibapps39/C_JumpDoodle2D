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
    float max_x = visible_area.x - size.x;
    float max_y = visible_area.y - size.y;
    return (Platform){
        .position = (Vector2){
            .x = GetRandomValue(0, max_x),
            .y = GetRandomValue(0, max_y),
        },
        .size = size,
        .color = get_random_color(),
    };
}

void populate_platforms(
    Platform PA[ON_SCREEN_PLATFORM_COUNT],
    Vector2 visible_area,
    Vector2 platform_size,
    float jump_height)
{
    const int num_sectors = ON_SCREEN_PLATFORM_COUNT;
    const float sector_height = visible_area.y / num_sectors;
    const float max_x = fmaxf(0.0f, (visible_area.x - platform_size.x));
    const float jump_clearance = fabsf(jump_height)*0.9f;

    for (int i = 0; i < num_sectors; i++)
    {
        float min_y = sector_height * i;
        // Ensure that platforms are not too tall 
        float max_y =  ( ( sector_height * (i + 1) ) - platform_size.y ) - jump_clearance;
        max_y = fmaxf(min_y, max_y);

        PA[i] = (Platform){
            .position = (Vector2){
                .x = GetRandomValue(0, (int)max_x),
                .y = GetRandomValue((int)min_y, (int)max_y)},
            .color = get_random_color(),
            .size = platform_size
        };
    }
}

// [===== Progressive Platform Population =====]
void shift_platforms_down(Platform PA[ON_SCREEN_PLATFORM_COUNT], float dy)
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    { 
        PA[i].position.y += dy;
    }
}

void draw_platforms(Platform platform_array[ON_SCREEN_PLATFORM_COUNT])
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(platform_array[i].position, platform_array[i].size, platform_array[i].color);
    }
}
