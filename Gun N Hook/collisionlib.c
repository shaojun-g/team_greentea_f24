#include "collision_utils.h"
#include "cprocessing.h"
#include "collisionlib.h"

// function to prevent overlap of player and platforms.
void collide_platform(float* player_x, float* player_y, float* player_width, float* player_height, float* platform_x, float* platform_y, float* platform_width, float* platform_height) {
	// if player is intersecting with platform.
	if (c_rect_rect(*player_x, *player_y, *player_width, *player_height, *platform_x, *platform_y, *platform_width, *platform_height)) {
		// player is above platform
		if (*player_y < (*platform_y - *platform_height / 2))
			// push player up to prevent overlap with platform.
			*player_y = *platform_y - ((*player_height / 2) + (*platform_height / 2));
	}
}

// function that causes player to take damage when colliding with enemies or enemy projectiles.
void player_damage(float* player_x, float* player_y, float* player_width, float* player_height, float* enemy_x, float* enemy_y, float* enemy_width, float* enemy_height, int* player_HP, int* projectile_Live) {
	if (c_rect_rect(*player_x, *player_y, *player_width, *player_height, *enemy_x, *enemy_y, *enemy_width, *enemy_height))
		if (*projectile_Live) {
			*player_HP -= 1;
			*projectile_Live = 0;
			printf("enemy bullet detected");
		}
}

// function that causes enemies to take damage when colliding with player projectiles.
void deal_damage(Bullet bullets[], float *char_x, float* char_y, float* char_width, float* char_height, int* char_HP) {
	float time_elapsed = 0.0;
	time_elapsed += CP_System_GetDt();


	for (int i = 0; i < 50; ++i) {
		if (c_rect_rect(bullets[i].x, bullets[i].y, bullets[i].diameter, bullets[i].diameter, *char_x, *char_y, *char_width, *char_height) && bullets[i].live == 1) {
			bullets[i].live = 2;
			*char_HP -= 1;
		}
	}
}

//	initialize pea_shooter bullets.
void pea_shooter_init(Bullet bullets[], float* player_x, float* player_y) {
	for (int i = 0; i < 50; ++i) {
		bullets[i].x = *player_x;
		bullets[i].y = *player_y;
		bullets[i].diameter = 12.5;
		bullets[i].speed = 800.0;
		bullets[i].live = 0;
	}
}

//	pea-shooter function.
void pea_shooter(Bullet bullets[], float* player_x, float* player_y) {
	CP_Color colorCyan = CP_Color_Create(100, 250, 250, 255);

    // if mouse triggered, make live 1 bullet
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
        float mouse_click_x = CP_Input_GetMouseX();
		for (int i = 0; i < 50; ++i) {
			if (!(bullets[i].live))
				bullets[i].live = 1;
			else
				continue;
			// if speed is positive and mouse clicked left of player, negative the speed.
			if ((*player_x - mouse_click_x) > 0 && bullets[i].speed > 0)
				bullets[i].speed = -bullets[i].speed;
			// if speed is negative and mouse clicked right of player, negative the speed.
			else if ((*player_x - mouse_click_x) < 0 && bullets[i].speed < 0)
				bullets[i].speed = -bullets[i].speed;
			// if managed to make a bullet live, break the loop.
			break;
		}
	}

	//	for loop to update every bullet; draw bullet and update x coordinate.
	for (int i = 0; i < 50; ++i) {
		//	if bullet is not live, reset position
		if (!(bullets[i].live)) {
			bullets[i].x = *player_x;
			bullets[i].y = *player_y;
		}

		if (bullets[i].live) {
			// draw bullet if alive.
			CP_Settings_Fill(colorCyan);
			CP_Graphics_DrawCircle(bullets[i].x, bullets[i].y, bullets[i].diameter);
			// change bullet speed 
			bullets[i].x += bullets[i].speed * CP_System_GetDt();

			// when out of screen, unalive the bullet
			if (bullets[i].x > 1650 || bullets[i].x < -50)
				bullets[i].live = 0;
		}
	}

	
}