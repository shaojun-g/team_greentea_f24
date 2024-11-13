#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "player.h"



//Basic Movement for player
void basic_movement(double* player_x, double* player_y, double* speed_x, double* speed_y, int* on_ground, double dt) {
	if (CP_Input_KeyDown(KEY_D)) {
		*speed_x = 300;
		*player_x += *speed_x * dt;
	}

	if (CP_Input_KeyDown(KEY_A)) {
		*speed_x = -300;
		*player_x += *speed_x * dt;
	}

	if (*on_ground == 1) {
		double starting_x = *player_x;
		double max_jump = 200;
		if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_SPACE)) {
			if (*speed_y < 1500) {
				*speed_y += 100;
				*player_y -= *speed_y * dt;
			}
			else {
				*on_ground = 0;
			}
		}
		if (CP_Input_KeyReleased(KEY_W) || CP_Input_KeyReleased(KEY_SPACE)) {
			*on_ground = 0;
		}
	}

}


void gravity(double* player_y, double* speed_y, double dt) {
	*speed_y = 500;
	*player_y += *speed_y * dt;
}
