#include "main.h"

int main(void)
{

    float window_width = DEFAULT_WINDOW_X;
    float window_height = DEFAULT_WINDOW_Y;
    float center_x = window_width / 2;
    float center_y = window_height / 2;
    float screen_bottom = window_height;
    const Vector2 SCREEN_CENTER = (Vector2){.x = center_x, .y = center_y};
    InitWindow(window_width, window_height, "C_JUMPDOODLE_2D");
    SetTargetFPS(60);

    Camera2D camera = (Camera2D){0};
    camera = init_cam(camera, SCREEN_CENTER);

    Player player = init_player(
        SCREEN_CENTER, DEFAULT_PLAYER_SIZE, DEFAULT_PLAYER_COLOR
    );

    Vector2 platform_pos = (Vector2){.x = center_x/3, .y = screen_bottom-screen_bottom/3};
    Vector2 platform_size = (Vector2){.x = .0333*window_width*9, .y = .0667*window_height};
    Rectangle platform_hitbox = (Rectangle){
        .x = platform_pos.x, .y = platform_pos.y, 
        .width = platform_size.x, .height = platform_size.y
    };
    Color platform_color = ORANGE;

    int check = 0;

    while (!WindowShouldClose())
    {
        move_xz(&player.position, DEFAULT_HORIZONTAL_SPEED);
        Gravity(&player.position);
        contain_player_debug(&player, window_height);
        if( check_hitbox(
            &player.position, 
            player.size.x, 
            player.size.y, 
            &platform_pos, 
            platform_size.x, 
            platform_size.y 
        ))
        {
            bounce(&player.position, .0333f*screen_bottom);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        //draw_platforms();
        draw_player(&player);
        DrawRectangleV(platform_pos, platform_size, platform_color);

        //DrawBoundingBox(player.hitbox, GREEN);

        EndMode2D();
        // Draw text showing players position
        DrawText(
            TextFormat("Player position: (%.2f, %.2f)", player.position.x, player.position.y),
            10,
            10,
            20,
            WHITE
        );
                DrawText(
            TextFormat("check_bounce: %i)", check),
            40,
            40,
            20,
            WHITE
        );
        EndDrawing();
    }
    CloseWindow();
    return 0;
}