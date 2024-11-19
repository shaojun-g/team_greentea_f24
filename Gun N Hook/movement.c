#include "cprocessing.h"
#include <stdio.h>;
#include <math.h>
#include "utils.h";
#include "movement.h"
#include "collision_utils.h"

void basic_movement(float* player_x, float* player_y, float* speed_x, float* speed_y, int* on_ground) {
	//	left right movement
	if (CP_Input_KeyDown(KEY_D)) {
		*speed_x = 250;
	}
	else if (CP_Input_KeyDown(KEY_A)) {
		*speed_x = -250;
	} else {
		*speed_x = 0;
	}

	//	hold down S key to drop down platform
	if (CP_Input_KeyDown(KEY_S)) {
		float time_start = CP_System_GetDt();
		float time_elapsed = CP_System_GetDt();

		time_elapsed += CP_System_GetDt();

		if (time_elapsed - time_start > 0.75)
			*on_ground = 0;
	}

	//	initial upward speed when jump.
	if ((CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_SPACE)) && *on_ground) {
		*speed_y = -400;
		*on_ground = 0;
	}
	//	hold down key to get hang time.
	if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_SPACE) && !(*on_ground)) {
		*speed_y += -10;
	}
	/*else if (CP_Input_KeyReleased(KEY_W) || CP_Input_KeyReleased(KEY_SPACE)) {
		*speed_y += 200;
	}*/

	////	translate player coordinates based on speed computed.
	//if ((*player_x > 30 && *speed_x > 0) || (*player_x < 1570 && *speed_x < 0)) {
		*player_x += *speed_x * CP_System_GetDt();
	
	//if ((*player_y > 30 && *speed_y > 0) || (*player_y < 870 && *speed_y < 0)) {
		*player_y += *speed_y * CP_System_GetDt();
	
}

void gravity(float* speed_y) {
	//	increase downward speed as time passes.
	if (*speed_y < 1000 )	{
		*speed_y += 1600 * CP_System_GetDt(); 
	}
	//	set max speed.
	else				
	{ 
		*speed_y = 1500; 
	}
}

/*void basic_movement(float* player_x, float* player_y, float* speed_x, float* speed_y, int* on_ground, float dt) {
	if (CP_Input_KeyDown(KEY_D)) {
		*speed_x = 300;
		*player_x += *speed_x * dt;
	}

	if (CP_Input_KeyDown(KEY_A)) {
		*speed_x = -300;
		*player_x += *speed_x * dt;
	}
	else {
		*speed_x = 0;
	}

	if (*on_ground == 1) {
		float starting_x = *player_x;
		float max_jump = 200;
		if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_SPACE)) {
			if (*speed_y < 1500)  { // change this to change max height original is 1000
				*speed_y += 100;
				*player_y -= *speed_y * dt;
			}
			else {
				*on_ground = 0;
			}
		}
		if (CP_Input_KeyReleased(KEY_W) || CP_Input_KeyReleased(KEY_SPACE)) {
			*on_ground = 0;
			*speed_y = 500;
			*player_y += *speed_y * dt;
		}
	}
}

void gravity(float* player_y, float *speed_y, float dt) {
	*speed_y = 500;
	*player_y += *speed_y * dt;
}*/

int grapple_extending = 0;
float grapple_distance = 0;
float grapple_max_distance = 200.00;// max distance for grapple
float grapple_speed = 1000.0;
CP_Vector grapple_target;
float hook_x = 0.0;
float hook_y = 9.0;
float player_pulling = 0;
float player_grapple_speed = 500.0;// max grapple pulling speed
float cd_time = 1.0f; // cooldown tiimer
float cd_remaining = 0.0f;

void drawGrapple(Player *player, float* grapple_x, float* grapple_y, Platform* platforms, int num_of_platforms, float dt) {

	if (cd_remaining > 0.0f) {
		cd_remaining -= dt;
		if (cd_remaining < 0.0f) {
			cd_remaining = 0;
		}
	}

	if (cd_remaining == 0.0f && CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)) {
		float mouse_x = CP_Input_GetMouseX();
		float mouse_y = CP_Input_GetMouseY();
		CP_Vector direction = CP_Vector_Set((mouse_x - player->x), (mouse_y - player->y));
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

		*grapple_x = player->x + grapple_target.x * grapple_distance;
		*grapple_y = player->y + grapple_target.y * grapple_distance;

		int hit_platforms = 0;
		for (int i = 0; i < num_of_platforms; i++) {
			if (c_rect_point(platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height, *grapple_x, *grapple_y)) {
				printf("grapple hit!\n");
				hit_platforms = 1;

				// set hook location for pulling
				hook_x = *grapple_x;
				hook_y = *grapple_y;
				player_pulling = 1;

				//Stop grapple extension
				grapple_extending = 0;
				break;

				/**player_x = *grapple_x;
				player.y = *grapple_y;
				break;*/
			};
		}

		if (!hit_platforms && grapple_distance == grapple_max_distance) {
			grapple_extending = 0;
			grapple_distance = 0;
			cd_remaining = cd_time;
		}
	}

	if (player_pulling) {
		float distance_x = hook_x - player->x;
		float distance_y = hook_y - player->y;
		float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

		if (distance <= player->width) {
			float pull_back_x = (distance_x / distance) * player->width;
			float pull_back_y = (distance_y / distance) * player->width;

			player->x = hook_x - pull_back_x;
			player->y = hook_y - pull_back_y;
			player_pulling = 0;
			player->on_ground = 0;

			//*grapple_x = 0;
			//*grapple_y = 0;
			grapple_extending = 0;
			// make player go up platform with some nice accel.
			player->velocity.y += -400;

			cd_remaining = cd_time;
		}
		else {
			player->x += (distance_x / distance) * player_grapple_speed * dt;
			player->y += (distance_y / distance) * player_grapple_speed * dt;
		}
	}

	if (grapple_extending || player_pulling) {
		CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawLine(player->x, player->y, *grapple_x, *grapple_y);
	}

	if (cd_remaining > 0.0f) {
		float cd_width = 100.0f;
		float cd_height = 10.0f;
		float cd_fraction = 1.0f - (cd_remaining/cd_time);

		//cd background
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRect(player->x - cd_width / 2, player->y - 50.0f, cd_width, cd_height);
	
		//cd progress bar
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(player->x - cd_width / 2, player->y - 50.0f, cd_width * cd_fraction, cd_height);
	
	}

}