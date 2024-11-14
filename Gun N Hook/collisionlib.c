#include "collision_utils.h"
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