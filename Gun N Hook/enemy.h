#pragma once
//struct Platform {
//	float left_limit;
//	float right_limit;
//	float x_pos;
//	float y_pos;
//	float width;
//	float height;
//};
//struct Player {
//	float x_pos;
//	float y_pos;
//	float width;
//	float height;
//};
//MELEE enemy
enum MELEE_EnemyDir { //enemy only face left or right
	LEFT,
	RIGHT
};
enum MELEE_EnemyState { // only 3 states , do nothing , patrolling , attacking/chasing same thing
	IDLE,
	PATROL,
	ATTACK
};
struct MELEE_Enemy { //square enemy
	int health;
	float x_pos;
	float y_pos;
	float diameter;
	float width;
	float height;
	enum MELEE_EnemyState state;
	enum MELEE_EnemyDir dir;
	//enum EnemyDir dir;
}; // end of structs
//RANGE ENEMY
struct RANGE_Enemy {
	float x_pos;
	float y_pos;
	float width;
	float height;
	float shoot_posX;
	float shoot_posY;
};
struct Projectile {
	float x_pos;
	float y_pos;
	float diameter;
	float speed;
};

void EnemyState(struct MELEE_Enemy* e);
int playerOnPlat(float playerx, float plat_left_lim, float plat_right_lim);

void Enemy_Init(void);
void Enemy_Update(void);
void Enemy_Exit(void);