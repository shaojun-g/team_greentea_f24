// file:	enemy.h
// author:	Benjamin Ban
// email:	k.ban@digipen.edu
//
// brief:	declare functions
// Melee Enemy States : IDLE,PATROL,ATTACK
// -constraint to Platform it spawns at, hence need left right limit
// -chases Player if Player is on platform
// -stop chasing player after x Seconds if not on platform
// Range Enemy States - no states only shoot
// -have a shooting point where projectile spawn
// Copyright ? 2020 DigiPen, All rights reserved
//---------------------------------------------------------
#pragma once
#include "structs.h"

float midpoint(float p1,float p2);
void enemy_shoot_projectile(struct Projectile* projectile, struct RANGE_Enemy* enemy, float speed);
void state_change(struct MELEE_Enemy* enemy, struct Platform* platform, struct Player* player, float idletopatrol_sec,float attacktopatrol_sec,float elapsedTime_sec);
void EnemyState(struct MELEE_Enemy* e, struct Platform* plat, struct Player* player);
int playerOnPlat(float playerx, float plat_left_lim, float plat_right_lim);

void Enemy_Init(void);
void Enemy_Update(void);
void Enemy_Exit(void);