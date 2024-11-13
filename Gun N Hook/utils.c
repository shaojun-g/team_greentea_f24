#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "utils.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	//Calculate the half width and height of rectangle
	double HW = area_width / 2;
	double HH = area_height / 2;

	//Determine the boundary of the rectangle
	double left = area_center_x - HW;
	double right = area_center_x + HW;
	double top = area_center_y - HH;
	double bottom = area_center_y + HH;

	if (click_x >= left && click_x <= right && click_y >= top && click_y <= bottom) {
		return 1;
	}
	else {
		return 0;
	};
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	//Calculate the radius
	double radius = diameter / 2;

	//Calculate the distance between the click point and the circle's center
	double distance_squared = CP_Math_Square(click_x - circle_center_x) + CP_Math_Square(click_y - circle_center_y);

	if (distance_squared < CP_Math_Square(radius)) {
		return 1;
	}
	else {
		return 0;
	};
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	double distance = CP_Math_Distance(c2_x, c2_y, c1_x, c1_y);

	/*return ((distance <= (r1 + r2)) && (distance >= fabs(r1 - r2)) );*/
	if (distance < (r1 + r2)) {
		return 1;
	}
	else {
		return 0;
	}
}

void levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color)
{//determines if the cursor is over the button
	if (IsAreaClicked(area_center_x, area_center_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{//layers a translucent box over the button(giving that selection feel)
		CP_Color White = CP_Color_Create(255, 255, 255, 80);
		CP_Settings_Fill(White);
		CP_Graphics_DrawRect(area_center_x, area_center_y, area_width, area_height);
	}
	else {
		CP_Settings_Fill(color);
		CP_Graphics_DrawRect(area_center_x, area_center_y, area_width, area_height);
	}
}

void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color) 
{
	//CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	CP_Settings_Fill(color);
	CP_Graphics_DrawRect(area_center_x, area_center_y, area_width, area_height);
	levelselecthover(area_center_x, area_center_y, area_width, area_height, color);
}

void textwrite(const char* text, float x_position, float y_position, CP_Color color)
{
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(color);
	CP_Font_DrawText(text, x_position, y_position);

}

void draw_platform(platform platform) {
	//draw platforms
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(platform.platform_color);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(platform.x, platform.y, platform.width, platform.height);

}

void draw_goal(goal goal) {
	//draw goals
	goal.goal_color = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(goal.goal_color);
	CP_Graphics_DrawRectAdvanced(goal.x, goal.y, goal.width, goal.height, goal.degrees, goal.corner_radius);
}


int pause_menu(int game_state) {
	game_state = !game_state;

}