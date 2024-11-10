#pragma once
#define NUM_BOSS_PARTS 9
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

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
void draw_platform(Platform platform);
void draw_goal(goal goal);
void draw_boss(boss* boss);
void Restart_Level();