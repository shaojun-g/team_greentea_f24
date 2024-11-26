#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "utils.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelboss.h"
#include "mainmenu.h"
#include "structs.h"

#define BOSS_MAX_HEALTH 50
#define BOSS_HEALTHBAR_MAX_WIDTH 1400.00f


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

int AreC_RIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height)
{
	// Find the closest x-coordinate on the rectangle to the circle�s center
	float closest_x;
	if (circle_x < rect_x) {
		closest_x = rect_x; // Circle is to the left of the rectangle
	}
	else if (circle_x > rect_x + rect_width) {
		closest_x = rect_x + rect_width; // Circle is to the right of the rectangle
	}
	else {
		closest_x = circle_x; // Circle is within the horizontal bounds of the rectangle
	}

	// Find the closest y-coordinate on the rectangle to the circle�s center
	float closest_y;
	if (circle_y < rect_y) {
		closest_y = rect_y; // Circle is above the rectangle
	}
	else if (circle_y > rect_y + rect_height) {
		closest_y = rect_y + rect_height; // Circle is below the rectangle
	}
	else {
		closest_y = circle_y; // Circle is within the vertical bounds of the rectangle
	}

	// Calculate the distance between the circle�s center and this closest point
	float distance = CP_Math_Distance(circle_x, circle_y, closest_x, closest_y);

	// If the distance is less than or equal to the circle's radius, they intersect
	if (distance < radius) {
		return 1; // Intersection
	}
	else {
		return 0; // No intersection
	}
}


void draw_platform(Platform platform) {
	//draw platforms
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(platform.platform_color);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(platform.x, platform.y, platform.width, platform.height);

}

void draw_goal(Goal goal) {
	//draw goals
	goal.goal_color = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(goal.goal_color);
	CP_Graphics_DrawRectAdvanced(goal.x, goal.y, goal.width, goal.height, goal.degrees, goal.corner_radius);
}

void draw_healthbar(Healthbar healthbar){
	//draw a rectangle at the point
	CP_Settings_Fill(healthbar.rect_color);
	CP_Graphics_DrawRect(healthbar.x, healthbar.y, healthbar.width, healthbar.height);
}

void draw_boss(Boss* boss) {
	for (int i = 0; i < boss->num_parts; i++) {
		// draw_platform() draws a platform-like structure for parts of boss
		draw_platform(boss->parts[i]);
	}
}



void ApplyElasticCollision(Player* player, MELEE_Enemy hazard, float speed) {
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

	float bounce_back_distance = 2.0; //change this to determine distaance of bounceback

	// Check which side the collision occurred and adjust player position and velocity
	if (player_right > hazard_left && player_left < hazard_right) {
		 // Check if the player is moving right and collides with the left side of the hazard
		if (player->velocity.x >= 0 && player_right > hazard_left && player_left < hazard_left) {
			// Collision on the left side of the hazard
			player->x = hazard_left - player->width * bounce_back_distance;  // Adjust position to prevent overlap
			player->velocity.x *= -speed;  // Reverse the horizontal velocity (bounce)
		}
		// Check if the player is moving left and collides with the right side of the hazard
		else if (player->velocity.x <= 0 && hazard_right - player_left < player->width) {
			// Collision on the right side of the hazard
			player->x = hazard_right + player->width * bounce_back_distance;
			player->velocity.x *= speed;
		}
	}
	
	if (player_bottom > hazard_top && player_top < hazard_bottom) {
		if (player->velocity.y > 0 && player_bottom - hazard_top < player->height) { 
			// Collision on the top
			player->y = hazard_top - player->height * bounce_back_distance;
			player->velocity.y *= -speed; // Bounce back vertically
			player->on_ground = 1;  //mark as grounded after landing
		}
		else if (player->velocity.y < 0 && hazard_bottom - player_top < player->height) { 
			// Collision on the bottom
			player->y = hazard_bottom;
			player->velocity.y *= -speed;
		}
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
	// set rectangle x & y position 
	CP_Settings_RectMode(CP_POSITION_CENTER);
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

//void draw_platform(Platform platform) {
//	//draw platforms
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//	CP_Settings_Fill(platform.platform_color);
//	CP_Settings_NoStroke();
//	CP_Graphics_DrawRect(platform.x, platform.y, platform.width, platform.height);
//
//}

//void draw_goal(Goal goal) {
//	//draw goals
//	goal.goal_color = CP_Color_Create(0, 0, 0, 255);
//	CP_Settings_Fill(goal.goal_color);
//	CP_Graphics_DrawRectAdvanced(goal.x, goal.y, goal.width, goal.height, goal.degrees, goal.corner_radius);
//}

void pause_state(int *game_state) {
	if (*game_state == 0) {
		*game_state = (int)1;
	} else
	{
		*game_state = (int)0;
	}
}

void pause_menu(int *game_state,FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit) {

	//width and height of the window
	float width = CP_System_GetWindowWidth()/ 1.0f;
	float height = CP_System_GetWindowHeight()/ 1.0f;

	float xRect = CP_System_GetWindowWidth() / 2.0f;
	float yRect1 = CP_System_GetWindowHeight() / 4.6f;
	float yRect2 = CP_System_GetWindowHeight() / 1.9f;
	float yRect3 = CP_System_GetWindowHeight() / 1.2f;
	float rectW = CP_System_GetWindowWidth() / 4.4f;
	float rectH = CP_System_GetWindowHeight() / 4.4f;

	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	//CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	//font size
	CP_Settings_TextSize(50.f);

	if (game_state) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width, height);

		//continue button
		buttoncreate(xRect, yRect1, rectW, rectH, Blue);
		textwrite("Continue", xRect, yRect1, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				*game_state = 0;


			}
		}

		// restart button
		buttoncreate(xRect, yRect2, rectW, rectH, Blue);
		textwrite("Restart", xRect, yRect2, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameStateForced(currentlevel_init,currentlevel_update,currentlevel_exit);
			};
		};


		// exit button
		buttoncreate(xRect, yRect3, rectW, rectH, Blue);
		textwrite("Exit to main menu", xRect, yRect3, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect3, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			};
		};

		CP_Settings_TextSize(25.00f);
	}
}

void restart_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit) {

	//width and height of the window
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();

	float xRect = CP_System_GetWindowWidth() / 2.0f;
	//float yRect1 = CP_System_GetWindowHeight() / 4.6f;
	float yRect2 = CP_System_GetWindowHeight() / 1.9f;
	float yRect3 = CP_System_GetWindowHeight() / 1.2f;
	float rectW = CP_System_GetWindowWidth() / 4.4f;
	float rectH = CP_System_GetWindowHeight() / 4.4f;

	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	//CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_TextSize(50.f);

	if (game_state) {
		//white background
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width, height);

		//gameover text
		CP_Settings_TextSize(100.00f); // set text size to 50.0f
		textwrite("Game Over", CP_System_GetWindowWidth()/2.0f, 200, Black);
		CP_Settings_TextSize(50.00f); // set text size to 25.0f
		// restart button
		buttoncreate(xRect, yRect2, rectW, rectH, Blue);
		textwrite("Restart", xRect, yRect2, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameStateForced(currentlevel_init, currentlevel_update, currentlevel_exit);
			};
		};


		// exit button
		buttoncreate(xRect, yRect3, rectW, rectH, Blue);
		textwrite("Exit to main menu", xRect, yRect3, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect3, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			};
		};


	}
	CP_Settings_TextSize(25.00f);
}

void win_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit) {

	//width and height of the window
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();

	float xRect = CP_System_GetWindowWidth() / 2.0f;
	//float yRect1 = CP_System_GetWindowHeight() / 4.6f;
	float yRect2 = CP_System_GetWindowHeight() / 1.9f;
	float yRect3 = CP_System_GetWindowHeight() / 1.6f;
	float rectW = CP_System_GetWindowWidth() / 4.4f;
	float rectH = CP_System_GetWindowHeight() / 4.4f;

	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	//CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_TextSize(50.f);

	if (game_state) {
		//white background
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width, height);

		//gameover text
		CP_Settings_TextSize(100.00f); // set text size to 50.0f
		textwrite("You win!", CP_System_GetWindowWidth() / 2.0f, 300, Black);
		CP_Settings_TextSize(50.00f); // set text size to 25.0f


		// exit button
		buttoncreate(xRect, yRect3, rectW, rectH, Blue);
		textwrite("Exit to main menu", xRect, yRect3, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect3, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			};
		};


	}
	CP_Settings_TextSize(25.00f);
}
//int check_collision_rect(float proj_x, float proj_y, float proj_diameter,
//	float player_x, float player_y, float player_width, float player_height) {
//	return (proj_x + proj_diameter / 2 >= player_x &&
//		proj_x - proj_diameter / 2 <= player_x + player_width &&
//		proj_y + proj_diameter / 2 >= player_y &&
//		proj_y - proj_diameter / 2 <= player_y + player_height);
//}

//void update_projectile(Projectile* projectile, float player_x, float player_y, float player_width, float player_height, int* player_hp) {
//
//		if (check_collision_rect(projectile->x, projectile->y, projectile->diameter, player_x,  player_y,  player_width,  player_height)) {
//			(*player_hp)--;
//			printf("collison");
//		}
//}

//boss health bar update function
void update_boss_healthbar(Healthbar* health_bar, int current_health) {
	// Ensure health doesn't go below 0
	if (current_health < 0) current_health = 0;

	// Calculate health percentage (0.0 to 1.0)
	float health_percentage = (float)current_health / (float)BOSS_MAX_HEALTH;

	// Update health bar width
	health_bar->width = BOSS_HEALTHBAR_MAX_WIDTH * health_percentage;

	// For debugging - print values to see what's happening
	
}

void draw_hearts(heart heart[], int current_hp) {
	float spacing = 50.f;
	for (int i = 0; i < MAX_HEALTH; ++i) {
		float gap = spacing * i;
		// Only draw hearts up to current HP
		if (i < current_hp) {
			CP_Image_Draw(heart[i].heart, heart[i].x + gap, heart[i].y, heart[i].width, heart[i].height, 255);
		}
	}
}
