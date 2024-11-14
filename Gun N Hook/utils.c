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

int AreCircles_GoalIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height)
{
	// Find the closest point on the rectangle to the circle�s center
	float closest_x = fmax(rect_x, fmin(circle_x, rect_x + rect_width));
	float closest_y = fmax(rect_y, fmin(circle_y, rect_y + rect_height));

	// Calculate the distance between the circle�s center and this closest point
	double distance = CP_Math_Distance(circle_x, circle_y, closest_x, closest_y);

	// If the distance is less than or equal to the circle's radius, they intersect
	if (distance < radius) {
		return 1; // Intersection
	}
	else {
		return 0; // No intersection
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

void goal_function() {

}

void ApplyElasticCollision(Player* player, platform hazard, float restitution) {
	// Calculate the edges of the centered hazard rectangle
	float hazard_left = hazard.x - hazard.width / 2;
	float hazard_right = hazard.x + hazard.width / 2;
	float hazard_top = hazard.y - hazard.height / 2;
	float hazard_bottom = hazard.y + hazard.height / 2;

	// Calculate the edges of the player rectangle 
	float player_left = player->x - player->width / 2;
	float player_right = player->x + player->width / 2;
	float player_top = player->y - player->height / 2;
	float player_bottom = player->y + player->height / 2;

	float bounce_back_distance = 2.50; //change this to determine distaance of bounceback

	// Check which side the collision occurred and adjust player position and velocity
	if (player_right > hazard_left && player_left < hazard_right) {
		
		 // Check if the player is moving right and collides with the left side of the hazard
		if (player->velocity.x >= 0 && player_right > hazard_left && player_left < hazard_left) {
			printf("1");
			// Collision on the left side of the hazard
			player->x = hazard_left - player->width * bounce_back_distance;  // Adjust position to prevent overlap
			player->velocity.x *= -restitution;  // Reverse the horizontal velocity (bounce)
		}
		// Check if the player is moving left and collides with the right side of the hazard
		else if (player->velocity.x < 0 && hazard_right - player_left < player->width) {
			printf("2");
			// Collision on the right side of the hazard
			player->x = hazard_right + player->width * bounce_back_distance;
			player->velocity.x *= -restitution;
		}
	}

	if (player_bottom > hazard_top && player_top < hazard_bottom) {
		if (player->velocity.y > 0 && player_bottom - hazard_top < player->height) { 
			// Collision on the top
			player->y = hazard_top - player->height * bounce_back_distance;
			player->velocity.y *= -restitution; // Bounce back vertically
			player->on_ground = 1;  // Optional, mark as grounded after landing
		}
		else if (player->velocity.y < 0 && hazard_bottom - player_top < player->height) { 
			// Collision on the bottom
			player->y = hazard_bottom;
			player->velocity.y *= -restitution;
		}
	}
}