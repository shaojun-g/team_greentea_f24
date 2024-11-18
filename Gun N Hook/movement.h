#pragma once
#include "cprocessing.h"

void basic_movement(float*player_x,float*player_y, float*speed_x, float*speed_y, int *on_ground);

void gravity(float* speed_y);

void drawGrapple(float* player_x, float* player_y,float* grapple_x, float *grapple_y, Platform *platforms, int num_of_platforms, float dt);