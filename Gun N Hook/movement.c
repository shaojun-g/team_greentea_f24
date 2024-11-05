#include "cprocessing.h"
#include <stdio.h>;
#include "utils.h";
#include "game.h"


void basic_movement(float* player_x, float* player_y, float* speed_x, float* speed_y, int* on_ground, float dt) {
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

void gravity(float* player_y, float* speed_y, float dt) {
	*speed_y = 500;
	*player_y += *speed_y * dt;
}

void drawGrapple(float* player_x, float* player_y, float* grapple_x, float* grapple_y, float dt) {
	float end_x = 0;
	float end_y = 0;
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)) {
		float mouse_x = CP_Input_GetMouseX();
		float mouse_y = CP_Input_GetMouseY();
		printf("mouse x is: %lf and mouse y is: %lf\n", mouse_x, mouse_y);
		CP_Vector drawGrapple = CP_Vector_Set((mouse_x - *player_x), (mouse_y - *player_y));
		CP_Vector dir_norm = CP_Vector_Normalize(drawGrapple);

		float line_length = 500.00;
		*grapple_x = *player_x + dir_norm.x * line_length;
		*grapple_y = *player_y + dir_norm.y * line_length;

		printf("x is: %lf and y is: %lf\n", end_x, end_y);

	}
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawLine(*player_x, *player_y, *grapple_x, *grapple_y);
}