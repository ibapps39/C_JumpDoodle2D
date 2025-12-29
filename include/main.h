#pragma once
#include "raylib.h"
#include "raymath.h"
#include "defaults.h"

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

void draw_player(Player* player)
{
    DrawRectangleV(player->position, player->size, player->color);
}

Camera2D init_cam(Camera2D cam, Vector2 pos)
{
    cam.target = pos;
    cam.offset = pos;
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
    p->y+=.8;
}

void bounce(Vector2* p, const float bounce_dist)
{
    p->y -= bounce_dist;
}

void move_xz(Vector2* pos, const float HORIZONTAL_SPEED)
{
    if (IsKeyDown(KEY_A)) pos->x -= HORIZONTAL_SPEED;
    if (IsKeyDown(KEY_D)) pos->x += HORIZONTAL_SPEED;
}

int check_bounce(Rectangle* player, Rectangle* platform)
{
    return CheckCollisionRecs(*player, *platform);
}

void contain_player_debug(Player* player, float window_y_size)
{
    if (player->position.y > window_y_size)
    {
        player->position.y = 0;
    }
    
}

Rectangle get_hitbox(const Vector2* pos, float size_x, float size_y)
{
    return (Rectangle){
        .x = pos->x,
        .y = pos->y,
        .width = size_x,
        .height = size_y
    };
}
int check_hitbox(Vector2* u, float uw, float uh, Vector2* v, float vw, float vh)
{
    Rectangle ubox = (Rectangle){
        .x = u->x,
        .y = u->y,
        .width = uw,
        .height = uh
    };
    Rectangle vbox = (Rectangle){
        .x = v->x,
        .y = v->y,
        .width = vw,
        .height = vh
    };
    return CheckCollisionRecs(ubox, vbox);
}