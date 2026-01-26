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
    const float jump_clearance = fabsf(jump_height) * 0.9f;

    for (int i = 0; i < num_sectors; i++)
    {
        float min_y = sector_height * i;
        // Ensure that platforms are not too far apart
        float max_y = ((sector_height * (i + 1)) - platform_size.y) - jump_clearance;
        max_y = fmaxf(min_y, max_y);

        PA[i] = (Platform){
            .position = (Vector2)
            {
                .x = GetRandomValue(0, (int)max_x),
                .y = sector_height*i
            },
            .color = get_random_color(),
            .size = platform_size};
    }
}

//[===== Progressive Platform Population =====]
void move_platforms_dy(
    Platform *PA, 
    float dy, 
    Vector2* player_pos, 
    Vector2 visible_area, 
    int num_platform, 
    float jump_force)
{
    int dont_move = (dy >= 0) || (player_pos->y >= visible_area.y/2);
    if (dont_move)
    {
        dy = 0;
        return;
    }
    
    for (size_t i = 0; i < num_platform; i++)
    {
        // increase the platform y value as the player's y value decreases
        
        PA[i].position.y += fabs(dy) + jump_force ;
        if (PA[i].position.y > GetScreenHeight() + PA[i].size.y)
        {
            int sign = (GetRandomValue(0,1) == 0) ? 1: -1;
            int x_max = GetScreenWidth() + (GetScreenWidth()/2)*sign;
            PA[i] = get_random_platform(PA[i].size, (Vector2){.x = x_max, .y = fabs(jump_force) });
        }
        if (PA[i].position.y <= jump_force*2)
        {
            PA[i].position.y += jump_force*2;
        }
        
    }
}

void draw_platforms(Platform platform_array[ON_SCREEN_PLATFORM_COUNT])
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(platform_array[i].position, platform_array[i].size, platform_array[i].color);
    }
}
