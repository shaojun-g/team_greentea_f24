// file:	enemy.c
// author:	Benjamin Ban
// email:	k.ban@digipen.edu
//
// brief:	create melee enemy and range enemy(to be used for boss too) and their states
// 
// Melee Enemy States : IDLE,PATROL,ATTACK
// -constraint to Platform it spawns at, hence need left limit and right limit
// -chases Player if Player is on platform
// -stop chasing player after x Seconds if not on platform
// 
// Range Enemy States - no states only shoot
// -have a shooting point where projectile spawn
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "enemy.h"
#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"
#include "game.h"
#include "movement.h"
#include "structs.h"
//MELEE_Enemy enemy1;
//RANGE_Enemy enemy2;
//RANGE_Enemy enemy3;
////struct Platform platform1;
////struct Player player1;
//Player player1;
//Platform platform1;
//Bullet bullet1;
//Bullet bullet2;
//CP_Font my_awesome_font;
//float elapsedTime;
//enemy state

void EnemyState( MELEE_Enemy* e,  Platform* plat,  Player* player) {
	switch (e->state) { // e->state same as (*e).state
	case IDLE:break;
	case PATROL:

		//printf("patrol state");
		if (e->dir == LEFT ) {
			e->x -= e->speed * CP_System_GetDt();
			if (e->x <= plat->left_limit) {
				e->x = plat->left_limit;// constraint to limit
				e->dir = RIGHT;
			}
		}
		if (e->dir == RIGHT ) {
			e->x += e->speed* CP_System_GetDt();
			if (e->x >= plat->right_limit) {
				e->x = plat->right_limit;// constraint to limit
				e->dir = LEFT;
			}
		}
		break;
	case ATTACK:
		if (e->x < player->x && e->x < plat->right_limit) {
			//if enemy is left of player move right
			e->x += (e->speed * CP_System_GetDt());
		}
		if (e->x > player->x && e->x > plat->left_limit) {
			//if enemy is right of player move left
			e->x -= (e->speed * CP_System_GetDt());
		}
		break;
	}
}
//float midpoint(float p1, float p2) {
//	return (p1 + p2) / 2;
//}
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
void state_change(MELEE_Enemy* enemy, Platform* platform, Player* player, float idletopatrol_sec, float attacktopatrol_sec,float *elapsedTime) {
	EnemyState(enemy, platform, player);
	*elapsedTime += CP_System_GetDt();
	//alternate patrol and idle
	if (*elapsedTime >= 3.0f && enemy->state == IDLE) {
		if (enemy->state != ATTACK) {
			enemy->state = PATROL;
			*elapsedTime = 0;
		}
	}
	else if (*elapsedTime >= 3.0f && enemy->state == PATROL) {
		if (enemy->state != ATTACK) {
			enemy->state = IDLE;
			*elapsedTime = 0;
		}
	}
	//prevent enemy from stuck at attack state
	if (*elapsedTime >= 8.0f && enemy->state == ATTACK) {
		enemy->state = PATROL;
		*elapsedTime = 0;
	}
	//change attack state if player within x(on plat) and y range(not too high or low from plat)
	if (playerOnPlat(player->x, platform->left_limit, platform->right_limit) == 1 &&
		(player->y >= platform->y - (player->width * 2) && player->y <= (platform->y - player->width / 2))) {
		*elapsedTime = 0;
		enemy->state = ATTACK;
	}
}
void enemy_shoot_projectile(Bullet* projectile,RANGE_Enemy* enemy, float speed) {
	if (projectile->live = 1) {
		switch (enemy->dir)
		{
		case LEFT:
			projectile->x -= speed * CP_System_GetDt();
			if (projectile->x < 0) {
				projectile->x = enemy->shoot_posX;
				projectile->live = 1;
			}
			break;
		case RIGHT:
			projectile->x += speed * CP_System_GetDt();
			if (projectile->x > CP_System_GetWindowWidth()) {
				projectile->x = enemy->shoot_posX;
				projectile->live = 1;
			}

		}
	}	
}

//void Enemy_Init(void)
//{
//	my_awesome_font = CP_Font_Load("Assets/Exo2-Regular.ttf");
//	//midpoint
//	//width
//	enemy1.width = 40;
//	//platform
//	platform1.x = 100;
//	platform1.y = 600;
//	platform1.width = 600;
//	platform1.height = 200;
//	platform1.left_limit = platform1.x; // 100
//	platform1.right_limit = platform1.x + platform1.width - enemy1.width; //660
//	float mid_plat = midpoint(platform1.x, platform1.x + platform1.width);
//	//melee enemy, melee xposition should be bounded to platform values
//	enemy1.x = mid_plat;
//	enemy1.y = platform1.y - enemy1.width;
//	enemy1.height = enemy1.width;
//	enemy1.state = IDLE;
//	enemy1.dir = RIGHT;
//	enemy1.health = 5;
//	enemy1.speed = 200;
//	// range enemy
//	enemy2.x = 800;
//	enemy2.y = 50;
//	enemy2.width = 100;
//	enemy2.height = 40;
//	enemy2.shoot_posX = enemy2.x;
//	enemy2.shoot_posY = enemy2.y + (enemy2.height / 2);
//	enemy2.dir = LEFT;
//	// range enemy
//	enemy3.x = 800;
//	enemy3.y = 100;
//	enemy3.width = 100;
//	enemy3.height = 40;
//	enemy3.shoot_posX = enemy3.x + enemy3.width;
//	enemy3.shoot_posY = enemy3.y + (enemy3.height / 2);
//	enemy3.dir = RIGHT;
//	//player
//	player1.x = 860;
//	player1.y = 560;
//	//player1.diameter = 30;
//	player1.width = 40;
//	player1.height = player1.width;
//
//	//projectile
//	bullet1.x = enemy2.shoot_posX;
//	bullet1.y = enemy2.shoot_posY;
//	bullet1.diameter = 15;
//	bullet1.live = 1;
//	//projectile
//	bullet2.x = enemy3.shoot_posX;
//	bullet2.y = enemy3.shoot_posY;
//	bullet2.diameter = 15;
//	bullet2.live = 1;
//
//	elapsedTime = 0;
//}
//
//void Enemy_Update(void) {
//	//void state_change(struct MELEE_Enemy* enemy, struct Platform* platform, struct Player* player, float idletopatrol_sec, float attacktopatrol_sec, float elapsedTime);
//	//idletopatrol_sec is how many seconds for enemy to  change from idle to patrol(NOT SO RANDOM MOVEMENT)
//	//attacktopatrol_sec is how many seconds for enemy to  change from attack to patrol(STOP CHASING PLAYER)
//	state_change(&enemy1, &platform1,&player1,3, 8, &elapsedTime);
//	//void enemy_shoot_projectile(struct Projectile* projectile, struct RANGE_Enemy* enemy, float speed);
//	enemy_shoot_projectile(&bullet1, &enemy2, 200);
//	enemy_shoot_projectile(&bullet2, &enemy3, 200);
//	
//	if (CP_Input_KeyDown(KEY_A)) { //move left when move left x--
//		//movement
//		player1.x -= 200* CP_System_GetDt();
//	} // end of check key A
//	else if (CP_Input_KeyDown(KEY_D)) { //move right when move right x++
//		//movement
//		player1.x += 200* CP_System_GetDt();
//	} // end of check key D
//
//	//background
//	CP_Graphics_ClearBackground(CP_Color_Create(122, 122, 122, 255));
//	//fake ground
//	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
//	CP_Graphics_DrawRect(platform1.x, platform1.y, platform1.width, platform1.height);
//	//melee_enemy
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(enemy1.x, enemy1.y, enemy1.width, enemy1.height);
//	//range_enemy
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(enemy2.x, enemy2.y, enemy2.width, enemy2.height);
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(enemy3.x, enemy3.y, enemy3.width, enemy3.height);
//	//player
//	CP_Settings_EllipseMode(CP_POSITION_CORNER);
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Graphics_DrawRect(player1.x, player1.y, player1.width, player1.height);
//	//draw projectile
//	CP_Settings_EllipseMode(CP_POSITION_CENTER);
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Graphics_DrawCircle(bullet1.x, bullet1.y, bullet1.diameter);
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Graphics_DrawCircle(bullet2.x, bullet2.y, bullet2.diameter);
//		// Create an array of characters (aka a string) that can store up to 256 characters.
//	char buffer[256];
//	// Fill the buffer with the text we want.
//	// Notice that it uses a similar syntax as printf()!
//	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
//	// Draw the text using the string stored in the buffer in the center of the screen.
//	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
//	CP_Font_DrawText(buffer, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 - 300);
//}
//
//void Enemy_Exit(void) {
//
//}