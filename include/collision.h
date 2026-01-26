#pragma once
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "platforms.h"
#include "defaults.h"


int check_hitbox(Vector2 *u_pos, float u_width, float u_height, Vector2 *v_pos, float v_width, float v_height)
{
    Rectangle ubox = (Rectangle){
        .x = u_pos->x,
        .y = u_pos->y,
        .width = u_width,
        .height = u_height};
    Rectangle vbox = (Rectangle){
        .x = v_pos->x,
        .y = v_pos->y,
        .width = v_width,
        .height = v_height};
    return CheckCollisionRecs(ubox, vbox);
}
void Gravity(Vector2 *speed_v, float g)
{
    speed_v->y += g;
}

void Friction(Vector2 *speed_v, float f)
{
    speed_v->x = f;
}

// onCollision per IsCollisionRecs() && speed_v > 0
void apply_force(Vector2 *speed_v, const float force, const float friction)
{
    speed_v->y = force;
    Friction(speed_v, friction);
}

void apply_collisions(Platform platform_array[ON_SCREEN_PLATFORM_COUNT], Player *player, int *collision_occured)
{
    *collision_occured = 0;
    for (size_t i = 0; i < ON_SCREEN_PLATFORM_COUNT; i++)
    {
        Platform p = platform_array[i];
        int touch = check_hitbox(
            &player->position, player->size.x, player->size.y, 
            &p.position, p.size.x, p.size.y) && player->speed.y > 0; // player->speed.y > 0 means falling
        if (touch)
        {
            *collision_occured = 1;
        }
    }
}

void on_collision(int* collision_occured, Player *player, Vector2 last_bounce_pos, float *score, float points_awareded, float bounce_force)
{
    if (!(*collision_occured)) return;
    apply_force(&player->speed, bounce_force, 5.0);
    last_bounce_pos = player->position;
    *score += points_awareded;
}

