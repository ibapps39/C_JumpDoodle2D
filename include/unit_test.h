#pragma once
#include "main.h"
#include "raylib.h"
#include "raymath.h"
#include "defaults.h"
#include <assert.h>

void min_total_platforms(int total_platforms)
{
    assert(total_platforms >= MIN_NUM_PLATFORMS);
}
