#pragma once
#include "cprocessing.h"

/*--------------------------------------------------------------------------------------------------------------------------------*/
//	PLAYER STRUCTS
/*--------------------------------------------------------------------------------------------------------------------------------*/

typedef struct {
	float x, y;  // x and y components of the velocity
} Velocity;

// Define a struct for Player
typedef struct {
	float x, y;  // x and y coordinates of the player position
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

/*--------------------------------------------------------------------------------------------------------------------------------*/
//	LEVEL & UI STRUCTS
/*--------------------------------------------------------------------------------------------------------------------------------*/

//initialize all platform structs
typedef struct Platform {

	double x;
	double y;
	double width;
	double height;
	CP_Color platform_color;

} Platform;

//initialize all goal structs
typedef struct goal {

	double x;
	double y;
	double width;
	double height;
	double degrees;
	double corner_radius;
	CP_Color goal_color;

}goal;

//initialize healthbar
typedef struct healthbar {
	double x;
	double y;
	double width;
	double height;
	CP_Color rect_color;
}healthbar;

//initialize boss
typedef struct boss {
	Platform parts[9];
	int num_parts;

}boss;
