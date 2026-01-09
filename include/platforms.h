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

// void fix_overlap(Platform* PA, float player_height)
// {
//     for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
//     {
//         if ( fabsf( PA[i].position.y - PA[i+1].position.y ) < PA[i].size.y)
//         {
//             int sign = GetRandomValue(LEFT, RIGHT);
//             PA[i].position.y -= fmax(PA[i].size.y*2, PA[i+1].size.y*2)*sign;
//         };

//         if ( fabsf( PA[i].position.x - PA[i+1].position.x ) < PA[i].size.x)
//         {
//             int sign = GetRandomValue(LEFT, RIGHT);
//             PA[i].position.x += fmax(PA[i].size.x*2, PA[i+1].size.x*2)*sign;
//         };
//     }
// }
// Maybe just break up the screen into sections and assign platforms to each section?
// void fix_platform_height(Platform* PA, Vector2 last_jump_pos, float force)
// {
//     float num_sectors = GetScreenHeight() / ON_SCREEN_PLATFORM_COUNT;
//     float bottom = GetScreenHeight();
//     for (int i = 0; i < num_sectors; i++)
//     {
//         if (PA[i].position.y > max_height)
//         {
//             PA[i].position.y =  max_height;
//         }
//     }
// }

void fix_not_on_screen(Platform *PA, Vector2 visible_area)
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        if (PA[i].position.y > visible_area.y - PA[i].size.y)
        {
            PA[i].position.y = visible_area.y - PA[i].size.y;
        }
        if (PA[i].position.y < 0)
        {
            PA[i].position.y = 0;
        }
        if (PA[i].position.x > visible_area.x - PA[i].size.x)
        {
            PA[i].position.x = visible_area.x - PA[i].size.x;
        }
        if (PA[i].position.x < 0)
        {
            PA[i].position.x = 0;
        }
    }
}

// void populate_platforms(
//     Platform PA[ON_SCREEN_PLATFORM_COUNT],
//     Vector2 visible_area,
//     Vector2 size,
//     float player_height,
//     Vector2 last_jump_pos,
//     float force
// )
// {
//     for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
//     {
//         PA[i] = get_random_platform(size, visible_area);
//     }
//     fix_overlap(PA, player_height);
//     //fix_platform_height(PA, last_jump_pos, force);
//     fix_not_on_screen(PA, visible_area);
// }

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

void draw_platforms(Platform platform_array[ON_SCREEN_PLATFORM_COUNT])
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(platform_array[i].position, platform_array[i].size, platform_array[i].color);
    }
}
