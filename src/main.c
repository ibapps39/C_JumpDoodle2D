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
    const Vector2 window_dim = (Vector2){.x = window_width, .y =window_height };
    InitWindow(window_width, window_height, "C_JUMPDOODLE_2D");
    SetTargetFPS(60);

    // [=====CAMERA INITIALIZATION=====]
    Camera2D camera = (Camera2D){0};
    camera = init_cam(camera, SCREEN_CENTER);

    // [=====PLAYER INITIALIZATION=====]
    // const float ORIGINAL_PLAYER_SIZE = DEFAULT_PLAYER_SIZE.y;
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
    int is_collision = 0;

    float score = 0.0f;
    float scroll_speed = 0.0f;

    Platform platform_array[ON_SCREEN_PLATFORM_COUNT];
    //[======Initial Population of Platform====]
    populate_platforms(
        platform_array,
        (Vector2){.x = window_width, .y = window_height},
        platform_size,
        bounce_force);
    assert(sizeof(platform_array) / sizeof(platform_array[0]) > 0);
    Vector2 last_bounce_pos = V2Zero;
    while (!WindowShouldClose())
    {

        float py = player.position.y;
        float px = player.position.x;
        //[=====RESET PLATFORMS=====]
        if (IsKeyPressed(KEY_Q))
        {
            populate_platforms(
                platform_array,
                (Vector2){.x = window_width, .y = window_height},
                platform_size,
                bounce_force);
        }
        // [===== MAKE GAME ACTIVE =====]
        if (game_state == ACTIVE)
        {
            move_xz(&player.position, minimum_x_speed, &player.speed.x);
            move_y(&player.position.y, &player.speed.y);
            Gravity(&player.speed, g);
            score += 0.01f;
            // move_platforms_down(&platform_array, scroll_speed, window_dim);
            parallax(window_width, window_height, player.position.y - py, player.position.x - px, GetFrameTime());
            draw_platforms(platform_array);
            draw_player(&player);
        }

        // [===== APPLY COLLISION =====]
        apply_collisions(platform_array, &player, &is_collision);
        // [===== ON COLLISION =====]
        on_collision(&is_collision, &player, last_bounce_pos, &score, 10.0f, bounce_force);

        move_platforms_down(platform_array, fabsf(player.position.y-py), window_dim, -bounce_force/2, player.position);

        // [===== ENSURE PLAYER HAS PLATFORM TO JUMP FROM AT START =====]
        if (score < 1)  {
            platform_array[0].position = (Vector2){.x = player.position.x, .y = player.position.y - 10};
        }

        // [===== CONTAIN PLAYER =====]
        contain_player_debug(&player, (Vector2){.x = window_width, .y = window_height}, 0);

        // [===== GAME OVER =====]
        if ((player.position.y >= (screen_bottom - player.size.y)) && is_falling(player.speed.y))
        {
            draw_game_over_screen((Vector2){.x = window_width, .y = window_height});
            game_state = INACTIVE;
        }
        // [===== DEBUG: FREEZE GAME =====]
        if (IsKeyPressed(KEY_S))
        {
            game_state = freeze_game(game_state);
        }
        // [===== RESET GAME =====]
        if (IsKeyPressed(KEY_R))
        {
            game_reset(
                &player,
                SCREEN_CENTER,
                &game_state,
                platform_array,
                platform_size,
                bounce_force,
                window_width,
                window_height);
            score = 0.0f;
            parallax(window_width, window_height, player.position.y - py, player.position.x - px, GetFrameTime());
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        int text_start_y = 40;
        DrawText(TextFormat("Score: %.2f", score), SCREEN_CENTER.x, text_start_y, 20, RAYWHITE);
        // DrawText(TextFormat("Is Falling: %i", is_falling(player.speed.y)), 10, text_start_y, 20, RAYWHITE);
        // DrawText(TextFormat("screen bottom - py: %.2f", screen_bottom - py), 10, text_start_y += 20, 20, RAYWHITE);
        // DrawText(TextFormat("Last Recorded VY Speed: x: %.2f y: %.2f", player.speed.x, player.speed.y), 10, text_start_y += 20, 20, PINK);
        // DrawText(TextFormat("Player x: %.2f y: %.2f", px, py), 10, text_start_y += 20, 20, WHITE);
        // DrawText(TextFormat("Collision %i", is_collision), 10, text_start_y += 20, 20, WHITE);
        
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}