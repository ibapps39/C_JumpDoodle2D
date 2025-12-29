#pragma once
#include "raylib.h"
#include "raymath.h"

#define DEFAULT_WINDOW_X 600
#define DEFAULT_WINDOW_Y 600
#define DEFAULT_RESOLUTION (int)DEFAULT_WINDOW_X *(int)DEFAULT_WINDOW_Y
#define DEFAULT_CENTER_SCREEN (Vector2){.x = DEFAULT_WINDOW_X / 2, .y = DEFAULT_WINDOW_Y / 2}

#define DEFAULT_HORIZONTAL_SPEED 5.0f
#define DEFAULT_VERTICAL_SPEED 5.0f
#define DEFAULT_JUMP_HEIGHT 5.0f

#define DEFAULT_PLAYER_SIZE (Vector2){.x = 2, .y = 4}
#define DEFAULT_PLAYER_COLOR (Color){.r = 0, .g = 255, .b = 0, .a = 255}


typedef struct Player
{
    Vector2 position;
    Vector2 size; // {.x = width , .y = height}
    Color color;
} Player;

typedef struct Platform
{
    Vector2 position;
    Vector2 size;
    Color color;
} Platform;

// On-screen platforms
#define ON_SCREEN_PLATFORM_COUNT 4
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

void draw_platforms()
{
    for (int i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        DrawRectangleV(PLATOFRMS[i].position, PLATOFRMS[i].size, PLATOFRMS[i].color);
    }
}

Camera2D init_cam(Camera2D cam, Vector2 pos)
{
    cam.target = pos;
    cam.offset = (Vector2){0};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;
    return cam;
}

Player init_player(Vector2 position, Vector2 size, Color color)
{
    Player player = {
        .position = position,
        .size = size,
        .color = color,
    };
    return player;
}

void Gravity(Vector2* p)
{
    p->y-=.2;
}

void bounce(Vector2* p)
{
    p->y += 1.5;
}

void move_xz(Vector2* pos, const float HORIZONTAL_SPEED)
{
    switch (GetKeyPressed())
    {
    case KEY_D:
        pos->x -= HORIZONTAL_SPEED;
        break;
    case KEY_A:
        pos->x += HORIZONTAL_SPEED;
        break;
    default:
        break;
    }
}