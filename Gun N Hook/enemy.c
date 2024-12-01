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
int playerOnPlat(float playerx, float plat_left_lim, float plat_right_lim) {
	if (playerx >= plat_left_lim && playerx <= plat_right_lim) {
		return 1;
	}
	else {
		return 0;
	}
	
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

