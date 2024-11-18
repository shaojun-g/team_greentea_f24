#pragma once
#include "utils.h"

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	player in contact with ground or platform.
*  @input	-	player position (x, y, width and height) + platform position (x, y, width and height)
*  @output	-	void but changes player position values depending on direction from platform to prevent overlap with platforms.	  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void collide_platform(Player* player, Platform* platform);

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	player hit by enemy projectile or collide with enemy.
*  @input	-	player position (x, y, width and height) + enemy/projectile position (x, y, width and height) + player_HP address.
*  @output	-	void but changes value in address of player_HP.																	  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
//void player_damage(float* player_x, float* player_y, float* player_width, float* player_height, float* enemy_x, float* enemy_y, float* enemy_width, float* enemy_height, int* player_HP, int* projectile_Live);

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* @brief	-	enemy hit by player pea-shooter projectile.
*  @input	-	player projectile position (x, y, width and height) + enemy position (x, y, width and height) + enemy_DamageCount
				address and *projectile_Live (to ensure projectiles only hit once).
*  @output	-	void but changes value in address of enemy_DamageCount.															  */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void deal_damage(Bullet bullets[], float* char_x, float* char_y, float* char_width, float* char_height, int* char_HP);

void pea_shooter_init(Bullet bullets[], float* player_x, float* player_y);

void pea_shooter(Bullet bullets[], float* player_x, float* player_y);
