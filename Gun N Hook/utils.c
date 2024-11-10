#include <math.h>
#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelboss.h"
#include "mainmenu.h"

int current_level = 0;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	//Calculate the half width and height of rectangle
	float HW = area_width / 2;
	float HH = area_height / 2;

	//Determine the boundary of the rectangle
	float left = area_center_x - HW;
	float right = area_center_x + HW;
	float top = area_center_y - HH;
	float bottom = area_center_y + HH;

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
	float radius = diameter / 2;

	//Calculate the distance between the click point and the circle's center
	float distance_squared = CP_Math_Square(click_x - circle_center_x) + CP_Math_Square(click_y - circle_center_y);

	if (distance_squared < CP_Math_Square(radius)) {
		return 1;
	}
	else {
		return 0;
	};
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	float distance = CP_Math_Distance(c2_x, c2_y, c1_x, c1_y);

	/*return ((distance <= (r1 + r2)) && (distance >= fabs(r1 - r2)) );*/
	if (distance < (r1 + r2)) {
		return 1;
	}
	else {
		return 0;
	}
}

void draw_platform(Platform platform) {
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
	CP_Graphics_DrawRect(healthbar.x, healthbar.y, healthbar.width, healthbar.height);
}

void draw_boss(boss* boss) {
	for (int i = 0; i < boss->num_parts; i++) {
		// draw_platform() draws a platform-like structure for parts of boss
		draw_platform(boss->parts[i]);
	}
}

void Restart_Level() {
	switch (current_level) {
	case 1:
		CP_Engine_SetNextGameState(Levelone_Init, Levelone_Update, Levelone_Exit);
		break;
	case 2:
		CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit);
		break;
	case 3:
		CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit);
		break;
		// Add more cases if you have additional levels
	default:
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		break;
	}
}
