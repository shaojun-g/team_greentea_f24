#include "collision_utils.h"
#include "collisionlib.h"
#include "cprocessing.h"

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
		}
}

// function that causes enemies to take damage when colliding with player projectiles.
void enemy_damage(float* PProjectile_x, float* PProjectile_y, float* PProjectile_width, float* PProjectile_height, float* enemy_x, float* enemy_y, float* enemy_width, float* enemy_height, int* enemy_DamageCount, int* projectile_Live) {
	if (c_rect_rect(*PProjectile_x, *PProjectile_y, *PProjectile_width, *PProjectile_height, *enemy_x, *enemy_y, *enemy_width, *enemy_height))
		if (*projectile_Live) {
			*enemy_DamageCount += 1;
			*projectile_Live = 0;
		}
}

// initial values for pea_shooters
void init_pea_shooter(Bullet bullets[], float* player_x, float* player_y) {
	//	initialize bullets array.
	for (int i = 0; i < 50; i++) {
		bullets[i].x = *player_x;
		bullets[i].y = *player_y;
		bullets[i].diameter = 35;
		bullets[i].speed = 800.0;
		bullets[i].live = 0;
	}
}

// pea-shooter function.
void pea_shooter(Bullet bullets[], float* player_x, float* player_y, float mouse_click_x) {
	CP_Color colorCyan = CP_Color_Create(100, 250, 250, 255);

	//	for loop to update every bullet; draw bullet and update x coordinate.
	for (int i = 0; i < 50; i++) {
		//	if bullet is not live and mouse is clicked
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

	// if mouse triggered, make live 1 bullet
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		for (int i = 0; i < 50; i++) {
			if (!(bullets[i].live)) {
				// if speed is positive and mouse clicked left of player, negative the speed.
				if ((*player_x - mouse_click_x) > 0 && bullets[i].speed > 0)
					bullets[i].speed = -bullets[i].speed;
				// if speed is negative and mouse clicked right of player, negative the speed.
				else if ((*player_x - mouse_click_x) < 0 && bullets[i].speed < 0)
					bullets[i].speed = -bullets[i].speed;

				bullets[i].live = 1;
			}
			else
				continue;

			break;
		}
	}
}
