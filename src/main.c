#include "main.h"

int main(void)
{

    float window_width = DEFAULT_WINDOW_X;
    float window_height = DEFAULT_WINDOW_Y;
    float center_x = window_width / 2;
    float center_y = window_height / 2;
    const Vector2 SCREEN_CENTER = (Vector2){.x = center_x, .y = center_y};

    InitWindow(window_width, window_height, "C_JUMPDOODLE_2D");
    SetTargetFPS(60);

    Player player = init_player(
        SCREEN_CENTER, DEFAULT_PLAYER_SIZE, DEFAULT_PLAYER_COLOR
    );
    Camera2D camera = (Camera2D){0};
    camera = init_cam(camera, SCREEN_CENTER);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        draw_platforms();
        draw_player(player);

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}