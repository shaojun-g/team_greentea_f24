#pragma once

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	player in contact with ground or platform.
*  @input	-	player position (x, y, width and height) + platform position (x, y, width and height)
*  @output	-	void but changes player position values depending on direction from platform to prevent overlap with platforms.	  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void collide_platform(float* player_x, float* player_y, float* player_width, float* player_height, float* platform_x, float* platform_y, float* platform_width, float* platform_height);

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	player hit by enemy projectile or collide with enemy.
*  @input	-	player position (x, y, width and height) + enemy/projectile position (x, y, width and height) + player_HP address.
*  @output	-	void but changes value in address of player_HP.																	  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void player_damage(float* player_x, float* player_y, float* player_width, float* player_height, float* enemy_x, float* enemy_y, float* enemy_width, float* enemy_height, int* player_HP, int* projectile_Live);

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	enemy hit by player pea-shooter projectile.
*  @input	-	player projectile position (x, y, width and height) + enemy position (x, y, width and height) + enemy_DamageCount
				address and *projectile_Live (to ensure projectiles only hit once).
*  @output	-	void but changes value in address of enemy_DamageCount.															  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void enemy_damage(float* PProjectile_x, float* PProjectile_y, float* PProjectile_width, float* PProjectile_height, float* enemy_x, float* enemy_y, float* enemy_width, float* enemy_height, int* enemy_DamageCount, int* projectile_Live);