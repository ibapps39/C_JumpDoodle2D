#pragma once
#include "raylib.h"
#include "raymath.h"

void animate_player_squish(Vector2* position, Vector2* size, int triggered, float dt)
{
    static float timer = 0.0f;          // Tracks time remaining in the "squish" phase
    const float duration = 1.0f;    // How long the squish lasts (seconds)
    const float recovery_speed = 15.0f; // Snappiness of the return
    const float intensity = 0.4f;       // Strength of the squish

    // 1. If the event happens, reset the timer to the full duration
    if (triggered) timer = duration;

    // 2. Logic Gate: Are we currently in a "Squish Event"?
    if (timer > 0)
    {
        // While timer is active, we push the size toward the "Squished" state
        float target_y = DEFAULT_PLAYER_SIZE.y * (1.0f - intensity);
        float target_x = DEFAULT_PLAYER_SIZE.x * (1.0f + intensity);
        
        size->x = Lerp(size->x, target_x, recovery_speed * dt);
        size->y = Lerp(size->y, target_y, recovery_speed * dt);

        timer -= dt; // Tick the timer down by actual seconds passed
    }
    else
    {
        // Timer is empty, return to normal size
        size->x = Lerp(size->x, DEFAULT_PLAYER_SIZE.x, recovery_speed * dt);
        size->y = Lerp(size->y, DEFAULT_PLAYER_SIZE.y, recovery_speed * dt);
    }

    // 3. The Height Correction
    // We adjust position only by the delta so the feet stay on the platform
    float height_diff = DEFAULT_PLAYER_SIZE.y - size->y;
    position->y += height_diff; 
}