// file:	collisionlib.c
// author:	Kwan
// email:
// 	
// co-author: Benjamin Ban
// email: k.ban@digipen.edu
// work done : modified Kwan's deal_damage function to work for enemy projectiles
// returns value 0 or 1(depending on if player is "damaged")
// parameters to be taken in Bullet,RANGE_Enemy,Player objects
// 
// brief: definition of functions from collisionlib.h
// 
// 
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "collision_utils.h"
#include "cprocessing.h"
#include "collisionlib.h"
#include "stdio.h"


// function to prevent overlap of player and platforms.
void collide_platform(Player* player, Platform* platform) {
	//	if player is intersecting with platform.
	if (c_rect_rect(player->x, player->y, player->width, player->height, platform->x, platform->y, platform->width, platform->height)) {
		//	if player is falling && above platform:
		if (player->velocity.y >= 0 && player->y < platform->y) {
			player->on_ground = 1;
			player->velocity.y = 0;
			player->y = platform->y - (platform->height / 2) - (player->height / 2);
			
		}
		if (player->x - player->width / 3 > platform->x + platform->width / 2 || player->x + player->width / 3 < platform->x - platform->width / 2)
			player->on_ground = 0;
	}
}

// function that causes enemies to take damage when colliding with player projectiles.
void deal_damage(Bullet bullets[], float *char_x, float* char_y, float* char_width, float* char_height, int* char_HP) {
	for (int i = 0; i < 50; ++i) {
		if (c_rect_rect(bullets[i].x, bullets[i].y, bullets[i].diameter, bullets[i].diameter, *char_x, *char_y, *char_width, *char_height) && bullets[i].live == 1) {
			bullets[i].live = 2;
			*char_HP -= 1;
		}
	}
}

// function that causes enemies to take damage when colliding with player projectiles.
int deal_damage_to_player(Bullet *projectile,RANGE_Enemy* rangenemy,Player* player) {
		if (c_rect_rect(projectile->x, projectile->y, projectile->diameter, projectile->diameter, player->x, player->y, player->width, player->height) && projectile->live == 1) {
			projectile->live = 2;		
			player->HP -=1;
			projectile->x = rangenemy->shoot_posX;
			projectile->y = rangenemy->shoot_posY;
			return 1;
		}
		return 0;
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
			if (!(bullets[i].live)) {
				// reset bullet locations when dead.
				bullets[i].x = *player_x;
				bullets[i].y = *player_y;
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
			
			// if managed to make a bullet live, break the loop.
			break;
		}
	}

	//	for loop to update every bullet; draw bullet and update x coordinate.
	for (int i = 0; i < 50; ++i) {
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