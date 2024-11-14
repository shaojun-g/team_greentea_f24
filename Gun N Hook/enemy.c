// file:	enemy.c
// author:	Benjamin Ban
// email:	k.ban@digipen.edu
//
// brief:	create melee enemy and range enemy
// 
// Melee Enemy States : IDLE,PATROL,ATTACK
// -constraint to Platform it spawns at, hence need left right limit
// -chases Player if Player is on platform
// -stop chasing player after x Seconds if not on platform
// 
// Range Enemy States - no states only shoot
// -have a shooting point where projectile spawn
// 
//
// init()
// update()
// shown as example can delete later
// 
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "enemy.h"
#include "cprocessing.h"
#include <stdio.h>

CP_Color black;
CP_Color red;
CP_Color green;
struct MELEE_Enemy enemy1;
struct RANGE_Enemy enemy2;
struct Platform platform1;
struct Player player1;
struct Projectile projectile1;
float speed;
float elapsedTime;
float dt;
//enemy state
void EnemyState(struct MELEE_Enemy* e) {
	switch (e->state) {
	case IDLE:break;
	case PATROL:
		//printf("patrol state");
		if (enemy1.dir == LEFT) {
			enemy1.x_pos -= speed+dt;
			if (enemy1.x_pos <= platform1.left_limit) {
				enemy1.dir = RIGHT;
			}
		}
		if (enemy1.dir == RIGHT) {
			enemy1.x_pos += speed+dt;
			if (enemy1.x_pos >= platform1.right_limit) {
				enemy1.dir = LEFT;
			}
		}
		break;
	case ATTACK:
		if (enemy1.x_pos < player1.x_pos &&enemy1.x_pos < platform1.right_limit) {
			//if enemy is left of player move right
			enemy1.x_pos += speed+dt;
		}
		if (enemy1.x_pos > player1.x_pos && enemy1.x_pos > platform1.left_limit) {
			//if enemy is right of player move left
			enemy1.x_pos -= speed+dt;
		}
		break;
	}
}

//checks if player on platform returns 1 if true, returns 0 if false
int playerOnPlat(float playerx, float plat_left_lim, float plat_right_lim) {
	if (playerx >= plat_left_lim && playerx <= plat_right_lim) {
		return 1;
	}
	else {
		return 0;
	}
	//player1.x_pos >= platform1.left_limit && player1.x_pos <= platform1.right_limit
}

void enemy_init(void)
{
	printf("hello world ");
	red = CP_Color_Create(255, 0, 0, 255);
	black = CP_Color_Create(0, 0, 0, 255);
	green = CP_Color_Create(0, 255, 0, 255);
	//melee enemy
	enemy1.x_pos = 150;
	enemy1.y_pos = 560;
	enemy1.width = 40;
	enemy1.height = enemy1.width;
	enemy1.state = IDLE;
	enemy1.dir = LEFT;
	enemy1.health = 5;
	// range enemy
	enemy2.x_pos = 800;
	enemy2.y_pos = 50;
	enemy2.width = 100;
	enemy2.height = 40;
	enemy2.shoot_posX = enemy2.x_pos;
	enemy2.shoot_posY = enemy2.y_pos + (enemy2.height)/2;
	//player
	player1.x_pos = 860;
	player1.y_pos = 560;
	player1.width = 40;
	player1.height = player1.width;
	//platform
	platform1.x_pos = 100;
	platform1.y_pos = 600;
	platform1.width = 600;
	platform1.height = 200;
	platform1.left_limit = platform1.x_pos; //100
	platform1.right_limit = platform1.x_pos + platform1.width - enemy1.width; //660
	//game stats
	speed = 5;
	elapsedTime = 0.0f;

	//projectile
	projectile1.x_pos = enemy2.shoot_posX;
	projectile1.y_pos = enemy2.shoot_posY;
	projectile1.diameter = 15;
}

void enemy_update(void) {

	// get dt and then print total elapsed time
	 dt = CP_System_GetDt();
	elapsedTime += dt;
	//alternate patrol and idle
	if (elapsedTime >= 3.0f && enemy1.state == IDLE) {
		if (enemy1.state != ATTACK) {
			enemy1.state = PATROL;
			elapsedTime = 0;
		}
	}
	else if (elapsedTime >= 3.0f && enemy1.state == PATROL) {
		if (enemy1.state != ATTACK) {
			enemy1.state = IDLE;
			elapsedTime = 0;
		}
	}
	//prevent enemy from stuck at attack state
	if (elapsedTime >= 8.0f && enemy1.state == ATTACK) { 
		enemy1.state = PATROL;
		elapsedTime = 0;
	}


	if (CP_Input_KeyDown(KEY_A)) { //move left when move left x--
		//movement
		player1.x_pos -= speed+dt;
	} // end of check key A
	else if (CP_Input_KeyDown(KEY_D)) { //move right when move right x++
		//movement
		player1.x_pos += speed+dt;
	} // end of check key D

	//background
	CP_Graphics_ClearBackground(CP_Color_Create(122, 122, 122, 255));
	//fake ground
	CP_Settings_Fill(green);
	CP_Graphics_DrawRect(100, 600, 600, 200);
	//melee_enemy
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect(enemy1.x_pos, enemy1.y_pos, enemy1.width, enemy1.height);
	//range_enemy
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect(enemy2.x_pos, enemy2.y_pos, enemy2.width, enemy2.height);
	//player
	CP_Settings_Fill(black);
	CP_Graphics_DrawRect(player1.x_pos, player1.y_pos, player1.width, player1.height);

	EnemyState(&enemy1);
	if (playerOnPlat(player1.x_pos,platform1.left_limit,platform1.right_limit) == 1) {
		elapsedTime = 0;
		enemy1.state = ATTACK;
	}

		CP_Settings_Fill(black);
		CP_Graphics_DrawCircle(projectile1.x_pos, projectile1.y_pos, projectile1.diameter);
		projectile1.x_pos -= 1 * speed + dt;
		if (projectile1.x_pos < 0) {
			projectile1.x_pos = enemy2.shoot_posX;
		}
	
	//collision
	//if (enemy.hit == 1) {
	//	enemy1.health -= 1;
	//}
}

void enemy_exit(void) {

}