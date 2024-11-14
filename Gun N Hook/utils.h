#pragma once

#define NUM_BOSS_PARTS 9

//define dt as time

//initialize all platform structs
typedef struct Platform {

	float x;
	float y;
	float width;
	float height;
	CP_Color platform_color;
	float left_limit, right_limit;
} Platform;


//int checkgrappleplat() {
//	if () {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}

//initialize all goal structs
typedef struct goal {

	float x;
	float y;
	float width;
	float height;
	float degrees;
	float corner_radius;
	CP_Color goal_color;

}goal;

//initialize healthbar
typedef struct healthbar {
	float x;
	float y;
	float width;
	float height;
	CP_Color rect_color;
}healthbar;

//initialize boss
typedef struct boss {
	Platform parts[NUM_BOSS_PARTS];
	int num_parts;

}boss;

typedef struct {
	double x, y;  // x and y components of the velocity
} Velocity;

// Define a struct for Player
typedef struct {
	double x, y;  // x and y coordinates of the player position
	double width;
	double height;
	int on_ground;
	Velocity velocity;  // Nested struct for velocity
} Player;



typedef struct {
	double x, y;  // x and y components of the velocity
	double on_wall;
} Grapple;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreCircles_GoalIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height);
void draw_platform(platform platform);
void draw_goal(goal goal);
void draw_boss(boss* boss);
void Restart_Level();
void goal_function();
void ApplyElasticCollision(Player* player, platform hazard, float restitution);