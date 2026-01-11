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

// void gen_platforms(
//     Platform PA[ON_SCREEN_PLATFORM_COUNT],
//     Vector2 visible_area,
//     Vector2 platform_size,
//     float jump_height,
//     Vector2* player_pos, 
//     float dy,
//     float dt
// )
// {
//     const int num_sectors = ON_SCREEN_PLATFORM_COUNT;
//     const float sector_height = visible_area.y / num_sectors;
//     const float max_x = fmaxf(0.0f, (visible_area.x - platform_size.x));
//     const float jump_clearance = fabsf(jump_height)*0.9f;
//     const float gen_point_h = visible_area.y/4.0f;
   
//     static float total_dy = 0.0f;
//     total_dy += dy*0.3;
//     float wrap_dy = fmodf(total_dy, gen_point_h);

//     for (int i = 0; i < num_sectors; i++)
//     {
//         float min_y = sector_height * i;
//         // Ensure that platforms are not too tall 
//         float max_y =  ( ( sector_height * (i + 1) ) - platform_size.y ) - jump_clearance;
//         max_y = fmaxf(min_y, max_y);

//         PA[i] = (Platform){
//             .position = (Vector2){
//                 .x = GetRandomValue(0, (int)max_x),
//                 .y = 0.0f
//             },
//             .color = get_random_color(),
//             .size = platform_size
//         };
//         // as player moves up, move platforms down
//         PA[i].position.y += dy
//     }
    
// }

void draw_platforms(Platform platform_array[ON_SCREEN_PLATFORM_COUNT])
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(platform_array[i].position, platform_array[i].size, platform_array[i].color);
    }
}
