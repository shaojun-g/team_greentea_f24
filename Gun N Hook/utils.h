#pragma once

#define NUM_BOSS_PARTS 9

//define dt as time

//initialize all platform structs
typedef struct platform {

	double x;
	double y;
	double width;
	double height;
	CP_Color platform_color;

} platform;

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
	platform parts[NUM_BOSS_PARTS];
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