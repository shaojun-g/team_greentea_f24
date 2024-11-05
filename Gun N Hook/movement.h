#pragma once
#include "cprocessing.h"

void basic_movement(float*player_x,float*player_y, float*speed_x, float*speed_y, int *on_ground, float dt);

void gravity(float* player_y, float *speed_y, float dt);

void drawGrapple(float* player_x, float* player_y,float* grapple_x, float *grapple_y, float dt);