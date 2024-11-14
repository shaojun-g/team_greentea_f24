#include "cprocessing.h"
#include <stdio.h>;
#include "utils.h";
#include "movement.h"
#include "collision_utils.h"

void basic_movement(float*player_x, float*player_y, float*speed_x, float*speed_y, int *on_ground, float dt) {
	if (CP_Input_KeyDown(KEY_D)) {
		*speed_x = 300;
		*player_x += *speed_x * dt;
	}

	if (CP_Input_KeyDown(KEY_A)) {
		*speed_x = -300;
		*player_x += *speed_x * dt;
	}

	if (*on_ground == 1) {
		float starting_x = *player_x;
		float max_jump = 200;
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

void gravity(float* player_y, float *speed_y, float dt) {
	*speed_y = 500;
	*player_y += *speed_y * dt;
}

int grapple_extending = 0;
float grapple_distance = 0;
float grapple_max_distance = 500.00;
float grapple_speed = 1000.0;
CP_Vector grapple_target;

void drawGrapple(float* player_x, float* player_y, float* grapple_x, float* grapple_y, platform* platforms, int num_of_platforms, float dt) {
	float end_x = 0;
	float end_y = 0;
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)) {
		float mouse_x = CP_Input_GetMouseX();
		float mouse_y = CP_Input_GetMouseY();
		CP_Vector direction = CP_Vector_Set((mouse_x - *player_x), (mouse_y - *player_y));
		CP_Vector dir_norm = CP_Vector_Normalize(direction);

		grapple_target = dir_norm;
		grapple_extending = 1;
		grapple_distance = 0;

	}

	if (grapple_extending) {
		grapple_distance += grapple_speed * dt;
		if (grapple_distance >= grapple_max_distance) {
			grapple_distance = grapple_max_distance;
			grapple_extending = 0;
		}

		*grapple_x = *player_x + grapple_target.x * grapple_distance;
		*grapple_y = *player_y + grapple_target.y * grapple_distance;

		int hit_platforms = 0;
		for (int i = 0; i < num_of_platforms; i++) {
			if (c_rect_point(platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height, *grapple_x, *grapple_y)) {
				printf("grapple hit!\n");
				hit_platforms = 1;
				*player_x = *grapple_x;
				*player_y = *grapple_y;
				break;
			};
		}

		if (hit_platforms) {
			grapple_extending = 0;
		}
		else if (!hit_platforms && grapple_distance == grapple_max_distance) {
			grapple_extending = 0;
			grapple_distance = 0;
		}
	}
	if (grapple_extending || (grapple_distance > 0 && !grapple_extending)) {
		CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawLine(*player_x, *player_y, *grapple_x, *grapple_y);
	}
}