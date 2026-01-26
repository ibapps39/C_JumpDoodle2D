#pragma once
#include "raylib.h"
#include "raymath.h"

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

Player init_player(Vector2 position, Vector2 size, Color color, Vector2 speed)
{
    Player player = {
        .position = position,
        .size = size,
        .color = color,
        .speed = (Vector2){0}};
    return player;
}