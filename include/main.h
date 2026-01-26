#pragma once

#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "defaults.h"
#include "gen_background.h"
#include "colors.h"
#include "collision.h"
#include "platforms.h"
#include "player.h"
#include "scroll_image.h"
#include "misc.h"
#include "unit_test.h"

typedef enum Game_States
{
    INACTIVE,
    ACTIVE
} Game_States;

Camera2D init_cam(Camera2D cam, Vector2 pos)
{
    cam.target = pos;
    cam.offset = pos;
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;
    return cam;
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
    float window_height)
{

    player->position = screen_center;
    player->speed = (Vector2){0};
    *game_state = ACTIVE;
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
    // if (player->position.y < 0)
    // {
    //     player->position.y = window_dim.y;
    // }
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


// or we could just dy now but, eh, this is fine
int is_falling(float player_y_speed)
{
    return player_y_speed > 0;
}

int freeze_game(Game_States pause)
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



void ACTIVE_game_loop(Game_States game_state, Player* player, float minimum_x_speed, float g, float *score)
{
            move_xz(&player->position, minimum_x_speed, &player->speed.x);
            move_y(&player->position.y, &player->speed.y);
            Gravity(&player->speed, g);
            *score += 0.01f;
}