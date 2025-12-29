#include "main.h"

typedef struct my_box
{
    Vector2 position;
    Vector2 size;
    Color color;
    Vector2 speed;
} my_box;

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

    my_box b = (my_box){
        .position = (Vector2){.x = center_x, .y = center_y},
        .size = (Vector2){.x = 10, .y = 35},
        .color = RED,
        .speed = (Vector2){.x = 0, .y = 0}};

    my_box b1 = (my_box){
        .position = (Vector2){.x = 0, .y = screen_bottom - center_y / 2},
        .size = (Vector2){.x = 1000, .y = 10},
        .color = YELLOW,
        .speed = (Vector2){.x = 0, .y = 0}};

        float g = 1.0f;
        float velocityY = 0.0f;
        float jump_force = -12.0f;

    while (!WindowShouldClose())
    {
        Rectangle br = get_hitbox(&b.position, b.size.x, b.size.y);
        Rectangle br1 = (Rectangle){ .x = b1.position.x, .y = b1.position.y, .width = b1.size.x, .height = b1.size.y };
        velocityY += g;
        b.position.y += velocityY;

        if (CheckCollisionRecs(br, br1) && velocityY > 0)
        {
            b.position.y = br1.y - b.size.y;
            velocityY = 0.0f;
            velocityY = jump_force;
        }
        
        if (b.position.y > screen_bottom) {
            b.position.y = 0;
            velocityY = 0; // It's okay to reset velocity here because the player "spawned"
        }

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        DrawRectangle(b.position.x, b.position.y, b.size.x, b.size.y, b.color);
        DrawRectangle(b1.position.x, b1.position.y, b1.size.x, b1.size.y, b1.color);

        EndMode2D();
        // Draw text showing players position

        EndDrawing();
    }
    CloseWindow();
    return 0;
}