#pragma once


typedef struct Platform {

	double x;
	double y;
	double width;
	double height;
	CP_Color platform_color;

} platform;

//initialize all goal structs
typedef struct Goal {

	double x;
	double y;
	double width;
	double height;
	double degrees;
	double corner_radius;
	CP_Color goal_color;

}goal;



int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
void levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);

//button functions
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);

//level functions
void draw_platform(platform platform);
void draw_goal(goal goal);

//pause functions
int pause_menu(int state);