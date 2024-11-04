#pragma once
#include "cprocessing.h"

void basic_movement(double*player_x,double*player_y, double*speed_x, double*speed_y, int *on_ground, double dt);

void gravity(double* player_y, double *speed_y, double dt);

void drawGrapple(double* player_x, double* player_y,double* grapple_x, double *grapple_y, double dt);