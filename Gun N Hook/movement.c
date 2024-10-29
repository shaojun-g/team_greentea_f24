#include "cprocessing.h"
#include <stdio.h>;
#include "utils.h";

void basic_movement(double*player_x, double*player_y, double*speed_x, double*speed_y, double dt) {
	if (CP_Input_KeyDown(KEY_D)) {
		*player_x += *speed_x * dt;
	}

	if (CP_Input_KeyDown(KEY_A)) {
		*player_x -= *speed_x * dt;
	}

	if (CP_Input_KeyDown(KEY_W)) {
		*player_y = *speed_y * dt;
	}

}

void grappling() {

}