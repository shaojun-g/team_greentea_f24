#pragma once
#include "cprocessing.h"

/*--------------------------------------------------------------------------------------------------------------------------------*/
//	PLAYER STRUCTS
/*--------------------------------------------------------------------------------------------------------------------------------*/

typedef struct {
	float x, y;  // x and y components of the velocity
} Velocity;

// Define a struct for Player
typedef struct Player {
	float x;
	float y;  // x and y coordinates of the player position
	float width;
	float height;
	int HP;
	int on_ground;
	Velocity velocity;  // Nested struct for velocity
} Player;

typedef struct {
	float x, y;  // x and y components of the velocity
	float on_wall;
} Grapple;

//	create bullet struct for pea-shooter.
typedef struct Bullet {
	float diameter;
	float x;
	float y;
	float speed;
	int live;
} Bullet;

//	array of bullet structs for pea-shooter.
struct Bullet bullets[50];

/*--------------------------------------------------------------------------------------------------------------------------------*/
//	ENEMY STRUCTS
/*--------------------------------------------------------------------------------------------------------------------------------*/

//	include enemy structs here

enum EnemyDir { //enemy only face left or right
	LEFT,
	RIGHT
};
//MELEE enemy
enum MELEE_EnemyState { // only 3 states , do nothing , patrolling , attacking/chasing same thing
	IDLE,
	PATROL,
	ATTACK
};
typedef struct { //square enemy
	//drawing variables
	float x;
	float y;
	float width;
	float height;
	//
	int health;
	float speed;
	enum MELEE_EnemyState state;
	enum EnemyDir dir;
	//enum EnemyDir dir;
}MELEE_Enemy; // end of struct
//RANGE ENEMY
typedef struct {
	//drawing variables
	float x;
	float y;
	float width;
	float height;
	//
	enum EnemyDir dir;
	float shoot_posX;
	float shoot_posY;
}RANGE_Enemy;
typedef struct {
	//drawing variables
	float x;
	float y;
	float diameter;
	float speed;
	//
	int travelling;
}Projectile;
/*--------------------------------------------------------------------------------------------------------------------------------*/
//	LEVEL & UI STRUCTS
/*--------------------------------------------------------------------------------------------------------------------------------*/

//initialize all platform structs
typedef struct Platform {
	float x;
	float y;
	float width;
	float height;
	CP_Color platform_color;
	float left_limit;
	float right_limit;
} Platform;

//initialize all goal structs
typedef struct Goal {

	float x;
	float y;
	float width;
	float height;
	float degrees;
	float corner_radius;
	CP_Color goal_color;

}Goal;

//initialize healthbar
typedef struct Healthbar {
	float x;
	float y;
	float width;
	float height;
	CP_Color rect_color;
}Healthbar;

//initialize boss
typedef struct Boss {
	Platform parts[9];
	int num_parts;

}Boss;
