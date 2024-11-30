// file:	movement.h
// author:	Shao Jun
// email:	shaojun.g@digipen.edu
// 
// brief: declaration of functions that affect player movement
// using WASD, gravity as well as definition of grapple function.	
// 
// Copyright @ 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"

void basic_movement(float*player_x,float*player_y, float*speed_x, float*speed_y, int *on_ground);

void gravity(float* speed_y);

void drawGrapple(Player *player,float* grapple_x, float *grapple_y, Platform *platforms, int num_of_platforms, float dt);