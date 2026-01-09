#include "main.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    // [=====WINDOW INITIALIZATION=====]
    float window_width = DEFAULT_WINDOW_X;
    float window_height = DEFAULT_WINDOW_Y;
    float center_x = window_width / 2;
    float center_y = window_height / 2;
    float screen_bottom = window_height;
    const Vector2 SCREEN_CENTER = (Vector2){.x = center_x, .y = center_y};
    InitWindow(window_width, window_height, "C_JUMPDOODLE_2D");
    SetTargetFPS(60);

    // [=====CAMERA INITIALIZATION=====]
    Camera2D camera = (Camera2D){0};
    camera = init_cam(camera, SCREEN_CENTER);

    // [=====PLAYER INITIALIZATION=====]
    Player player = init_player(
        SCREEN_CENTER, DEFAULT_PLAYER_SIZE, (Color){.r = 0, .g = 255, .b = 0, .a = 255}, (Vector2){0});

    // [=====PLATFORM INITIALIZATION=====]
    Vector2 platform_pos = (Vector2){.x = center_x / 3, .y = screen_bottom - screen_bottom / 3};
    Vector2 platform_size = (Vector2){.x = .0333 * window_width * 9, .y = .0667 * window_height};
    Rectangle platform_hitbox = (Rectangle){
        .x = platform_pos.x, .y = platform_pos.y, .width = platform_size.x, .height = platform_size.y};
    Color platform_color = ORANGE;
    // [=====GAME VARIABLE INITIALIZATION=====]
    const float GRAVITY = 1.0f;
    float g = GRAVITY;
    float texture_speed_y = 1.0f;
    const float minimum_x_speed = DEFAULT_HORIZONTAL_SPEED;

    int game_over_flag = 0;
    int game_state = ACTIVE;
    // save state player
    Player player_temp = (Player){0};
    float g_t = 0;
    float bounce_force = -24.0f;
    float friction = 5.0f;

    Platform platform_array[ON_SCREEN_PLATFORM_COUNT];

    populate_platforms(
        platform_array,
        (Vector2){.x = window_width, .y = window_height},
        platform_size,
        bounce_force
    );
    assert(sizeof(platform_array) / sizeof(platform_array[0]) > 0);
    Vector2 last_bounce_pos = V2Zero;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_Q))
        {
            populate_platforms(
        platform_array,
        (Vector2){.x = window_width, .y = window_height},
        platform_size,
        bounce_force
    );
        }
        if (game_state == ACTIVE)
        {
            move_xz(&player.position, minimum_x_speed, &player.speed.x);
            move_y(&player.position.y, &player.speed.y);
            Gravity(&player.speed, g);
        }

        for (size_t i = 0; i < 4; i++)
        {
            Platform p = platform_array[i];
            if (
                check_hitbox(
                    &player.position, player.size.x, player.size.y,
                    &p.position, p.size.x, p.size.y) &&
                player.speed.y > 0)
            {
                // player.position.y = platform_hitbox.y - player.size.y;
                onCollision(&player.speed, -24, 5.0);
                last_bounce_pos = player.position;
            }
        }

        contain_player_debug(&player, (Vector2){.x = window_width, .y = window_height}, 0);
        if (player.position.y <= 0)
        {

populate_platforms(
        platform_array,
        (Vector2){.x = window_width, .y = window_height},
        platform_size,
        bounce_force
    );
        }
        if (player.position.y >= screen_bottom && is_falling(player.speed.y))
        {
            game_over_flag = 1;
            game_over(&player, (Vector2){.x = window_width, .y = window_height});
            // player.speed = (Vector2){0};
        }
        if (IsKeyPressed(KEY_S))
        {
            game_state = freeze_game(game_state);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        genereate_random_background(window_width, window_height, &player.position);
        BeginMode2D(camera);
        draw_platforms(platform_array);
        draw_player(&player);
        DrawText(TextFormat("Speed Y: %.2f", player.speed.y), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Is Falling: %i", is_falling(player.speed.y)), 10, 40, 20, RAYWHITE);
        DrawText(TextFormat("GAME STATE: %i", game_state), 10, 60, 20, RAYWHITE);
        DrawText(TextFormat("Last Recorded VY Speed: x: %.2f y: %.2f", player_temp.speed.x, player_temp.speed.y), 10, 80, 20, PINK);

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}