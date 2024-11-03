#include <math.h>
#include <stdio.h>
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

void draw_healthbar(healthbar healthbar){
	//draw a rectangle at the point
	CP_Settings_Fill(healthbar.rect_color);
	//CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(healthbar.x, healthbar.y, healthbar.width, healthbar.height);
}

void draw_boss(boss* boss) {
	for (int i = 0; i < boss->num_parts; i++) {
		// Assuming draw_platform() can draw a platform-like structure
		draw_platform(boss->parts[i]);
	}
}