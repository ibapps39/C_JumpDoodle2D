#pragma once

#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "defaults.h"
#include "gen_background.h"
#include "colors.h"
#include "platforms.h"
#include "scroll_image.h"
#include "misc.h"

typedef struct Player
{
    Vector2 position;
    Vector2 size; // {.x = width , .y = height}
    Color color;
    Vector2 speed;
} Player;

void draw_player(Player *player)
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

Player init_player(Vector2 position, Vector2 size, Color color, Vector2 speed)
{
    Player player = {
        .position = position,
        .size = size,
        .color = color,
        .speed = (Vector2){0}};
    return player;
}

void Gravity(Vector2 *speed_v, float g)
{
    speed_v->y += g;
}
void Friction(Vector2 *speed_v, float f)
{
    speed_v->x = f;
}

void move_xz(Vector2 *pos, const float min_x_speed, float *speed_x)
{
    if (IsKeyDown(KEY_A))
        pos->x -= fabsf(min_x_speed + *speed_x);
    if (IsKeyDown(KEY_D))
        pos->x += fabsf(min_x_speed + *speed_x);
}
void move_y(float *pos_y_component, float *speed_y_component)
{
    *pos_y_component += *speed_y_component;
}

int check_bounce(Rectangle *player, Rectangle *platform)
{
    return CheckCollisionRecs(*player, *platform);
}

void game_reset(
    Player *player, 
    Vector2 screen_center, 
    int *game_state, 
    Platform *platform_array, 
    Vector2 platform_size, 
    float bounce_force, 
    float window_width, 
    float window_height
)
{

        player->position = screen_center;
        player->speed = (Vector2){0};
        *game_state = ACTIVE;
        populate_platforms(
            platform_array,
            (Vector2){.x = window_width, .y = window_height},
            platform_size,
            bounce_force);
}

void draw_game_over_screen(Vector2 screen_dim)
{
    ClearBackground(WHITE);
    DrawText("GAME OVER!", 200, 300, 50, RED);
    DrawText("Press R to Restart", 150, 360, 30, DARKGRAY);
}

void contain_player_debug(Player *player, Vector2 window_dim, int flags)
{
    if (player->position.y > window_dim.y && flags == 0)
    {
        player->position.y = 0;
    }
    if (player->position.y < 0)
    {
        player->position.y = window_dim.y;
    }
    if (player->speed.y > DEFAULT_MAX_SPEED_Y)
    {
        player->speed.y = 0;
    }
    if (player->position.x > window_dim.x)
    {
        player->position.x = 0;
    }
    if (player->position.x < 0)
    {
        player->position.x = window_dim.x;
    }
}

Rectangle get_hitbox(const Vector2 *pos, float size_x, float size_y)
{
    return (Rectangle){
        .x = pos->x,
        .y = pos->y,
        .width = size_x,
        .height = size_y};
}
int check_hitbox(Vector2 *u, float u_width, float u_height, Vector2 *v, float v_width, float v_height)
{
    Rectangle ubox = (Rectangle){
        .x = u->x,
        .y = u->y,
        .width = u_width,
        .height = u_height};
    Rectangle vbox = (Rectangle){
        .x = v->x,
        .y = v->y,
        .width = v_width,
        .height = v_height};
    return CheckCollisionRecs(ubox, vbox);
}

// onCollision per IsCollisionRecs() && speed_v > 0
void onCollision(Vector2 *speed_v, const float force, const float friction)
{
    speed_v->y = force;
    Friction(speed_v, friction);
}

// or we could just dy now but, eh, this is fine
int is_falling(float player_y_speed)
{
    return player_y_speed > 0;
}

int freeze_game(int pause)
{
    switch (pause)
    {
    case ACTIVE:
        return INACTIVE;
        break;
    case INACTIVE:
        return ACTIVE;
        break;
    default:
        break;
    }
}

Player copy_player_data(Player *p)
{
    return (Player){
        .position = p->position,
        .speed = p->speed,
        .color = p->color,
        .size = p->size};
}

Vector2 apply_collisions(Platform *platform_array[ON_SCREEN_PLATFORM_COUNT], Player *player)
{
    Vector2 last_bounce_pos;
    for (size_t i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        Platform p = **platform_array;
        if (
            check_hitbox(
                &player->position, player->size.x, player->size.y,
                &p.position, p.size.x, p.size.y) &&
            player->speed.y > 0)
        {
            onCollision(&player->speed, -24, 5.0);
            last_bounce_pos = player->position;
        }
    }
    return last_bounce_pos;
}