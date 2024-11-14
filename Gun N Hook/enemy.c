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
#include "utils.h"
#include "game.h"
#include "movement.h"
CP_Color black;
CP_Color red;
CP_Color green;
 MELEE_Enemy enemy1;
 RANGE_Enemy enemy2;
//struct Platform platform1;
//struct Player player1;
Player player1;
Platform platform1;
 Projectile projectile1;
float speed;
float elapsedTime;
float dt;
//enemy state
void EnemyState(MELEE_Enemy *e,Platform *plat,Player *player) {
	switch (e->state) { // e->state same as (*e).state
	case IDLE:break;
	case PATROL:
		//printf("patrol state");
		if (e->dir == LEFT) {
			e->x_pos -= speed+dt;
			if (e->x_pos <= plat->left_limit) {
				e->dir = RIGHT;
			}
		}
		if (e->dir == RIGHT) {
			e->x_pos += speed+dt;
			if (e->x_pos >= plat->right_limit) {
				e->dir = LEFT;
			}
		}
		break;
	case ATTACK:
		if (e->x_pos < player->x && e->x_pos < plat->right_limit) {
			//if enemy is left of player move right
			e->x_pos += speed+dt;
		}
		if (e->x_pos > player->x && e->x_pos > plat->left_limit) {
			//if enemy is right of player move left
			e->x_pos -= speed+dt;
		}
		break;
	}
}

float midpoint(float p1,float p2) {
	return (p1 + p2) / 2;
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

void Enemy_Init(void)
{
	printf("enemy.c called ");
	red = CP_Color_Create(255, 0, 0, 255);
	black = CP_Color_Create(0, 0, 0, 255);
	green = CP_Color_Create(0, 255, 0, 255);
	//midpoint
	float mid_plat = midpoint(100, 700);
	//width
	enemy1.width = 40;
	//platform
	platform1.x = 100;
	platform1.y = 600;
	platform1.width = 600;
	platform1.height = 200;
	platform1.left_limit = platform1.x; //100
	platform1.right_limit = platform1.x + platform1.width - enemy1.width; //660
	//melee enemy, melee xposition should be bounded to platform values
	enemy1.x_pos = mid_plat;
	enemy1.y_pos = platform1.y-enemy1.width;
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
	player1.x = 860;
	player1.y = 560;
	//player1.diameter = 30;
	player1.width = 40;
	player1.height = player1.width;
	//game stats
	speed = 5;
	elapsedTime = 0.0f;
	//projectile
	projectile1.x_pos = enemy2.shoot_posX;
	projectile1.y_pos = enemy2.shoot_posY;
	projectile1.diameter = 15;
	projectile1.travelling = 1;
}

void state_change(MELEE_Enemy *enemy,Platform *platform, Player* player,float idletoattack_sec, float attactopatrol_sec) {
	EnemyState(enemy, platform, player);
	dt = CP_System_GetDt();
	elapsedTime += dt;
	//alternate patrol and idle
	if (elapsedTime >= idletoattack_sec && enemy->state == IDLE) {
		if (enemy->state != ATTACK) {
			enemy->state = PATROL;
			elapsedTime = 0;
		}
	}
	else if (elapsedTime >= idletoattack_sec && enemy->state == PATROL) {
		if (enemy->state != ATTACK) {
			enemy->state = IDLE;
			elapsedTime = 0;
		}
	}
	//prevent enemy from stuck at attack state
	if (elapsedTime >= attactopatrol_sec && enemy->state == ATTACK) {
		enemy->state = PATROL;
		elapsedTime = 0;
	}
	//change attack state if player within x(on plat) and y range(not too high or low from plat)
	if (playerOnPlat(player->x, platform->left_limit, platform->right_limit) == 1 && 
		(player->y >= platform->y-(player->width*2) && player->y<= (platform->y-player->width/2))) {
		elapsedTime = 0;
		enemy->state = ATTACK;
	}
}

void enemy_shoot_projectile(struct Projectile* projectile,struct RANGE_Enemy* enemy , float speed) {
	dt = CP_System_GetDt();
	projectile->x_pos -= speed * dt;
	if (projectile->x_pos < 0) {
		projectile->x_pos = enemy->shoot_posX;
		projectile->travelling = 0;
	}
}

void Enemy_Update(void) {
	state_change(&enemy1, &player1,&platform1,3, 8);
	//EnemyState(&enemy1,&platform1,&player1);

	// get dt and then print total elapsed time
	//dt = CP_System_GetDt();
	//elapsedTime += dt;
	////alternate patrol and idle
	//if (elapsedTime >= 3.0f && enemy1.state == IDLE) {
	//	if (enemy1.state != ATTACK) {
	//		enemy1.state = PATROL;
	//		elapsedTime = 0;
	//	}
	//}
	//else if (elapsedTime >= 3.0f && enemy1.state == PATROL) {
	//	if (enemy1.state != ATTACK) {
	//		enemy1.state = IDLE;
	//		elapsedTime = 0;
	//	}
	//}
	////prevent enemy from stuck at attack state
	//if (elapsedTime >= 8.0f && enemy1.state == ATTACK) { 
	//	enemy1.state = PATROL;
	//	elapsedTime = 0;
	//}

	if (CP_Input_KeyDown(KEY_A)) { //move left when move left x--
		//movement
		player1.x -= speed+ CP_System_GetDt();
	} // end of check key A
	else if (CP_Input_KeyDown(KEY_D)) { //move right when move right x++
		//movement
		player1.x += speed+ CP_System_GetDt();
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
	CP_Settings_EllipseMode(CP_POSITION_CORNER);
	CP_Settings_Fill(black);
	//CP_Graphics_DrawCircle(player1.x, player1.y, player1.diameter);
	CP_Graphics_DrawRect(player1.x, player1.y, player1.width, player1.height);


	CP_Settings_EllipseMode(CP_POSITION_CENTER);
		CP_Settings_Fill(black);
	CP_Graphics_DrawCircle(projectile1.x_pos, projectile1.y_pos, projectile1.diameter);
	enemy_shoot_projectile(&projectile1, &enemy2, 5);
	//collision
	//if (enemy.hit == 1) {
	//	enemy1.health -= 1;
	//}
}

void Enemy_Exit(void) {}