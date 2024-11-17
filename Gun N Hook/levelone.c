#include "stdio.h"
#include "stdbool.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "leveltwo.h"
#include "levelone.h"
#include "collision_utils.h"
#include "movement.h"
#include "enemy.h"




CP_TEXT_ALIGN_HORIZONTAL h = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL v = CP_TEXT_ALIGN_V_MIDDLE;
Platform platform_base, platform1, platform2, platform_goal, hazard;
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
Player player;
Grapple grapple1 = { 0, 0, 0 };
float collisionCooldown = 0.0f;  // Cooldown timer for on_ground reset
float collisionCooldownDuration = 0.3f;  // Duration in seconds for cooldown
int health = 3;
float dt;
void Levelone_Init(void)
{

	//Set font size for all goal texts
	CP_Settings_TextSize(25.00f);
	CP_Settings_TextAlignment(h, v);
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);
	hazard.platform_color = CP_Color_Create(255, 128, 128, 255);
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform_base.x = CP_System_GetWindowWidth()/2;
	platform_base.y = 800.00;
	platform_base.width = CP_System_GetWindowWidth();
	platform_base.height = 10.00;
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform1.x = 1000.00;
	platform1.y = 650.00;
	platform1.width = 150.00;
	platform1.height = 15.00;
	//platform2 is second platform
	platform2.x = 1200.00;
	platform2.y = 500.00;
	platform2.width = 150.00;
	platform2.height = 15.00;
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform_goal.x = 1475.00;
	platform_goal.y = 350.00;
	platform_goal.width = 250.00;
	platform_goal.height = 15.00;
	//start goal will be where user spawns
	goal_start.x = 100.00;
	goal_start.y = 765.00;
	goal_start.width = 40.00;
	goal_start.height = 70.00;
	goal_start.corner_radius = 10;
	//end goal will be where user goes to next map
	goal_end.x = 1550.00;
	goal_end.y = 315.00;
	goal_end.width = 40.00;
	goal_end.height = 70.00;
	goal_end.corner_radius = 10;
	//player healthbar at top of map (will be rendered over everything else)
	player_health.x = 200.00;
	player_health.y = 50.00;
	player_health.width = 300.00;
	player_health.height = 20.00;
	//background of player healthbar
	player_health_background.x = 200.00;
	player_health_background.y = 50.00;
	player_health_background.width = 300.00;
	player_health_background.height = 20.00;

	CP_Settings_RectMode(CP_POSITION_CENTER);
	//to test hazard object
	hazard.x = 500.00;
	hazard.y = 750.00;
	hazard.width = 40.00;
	hazard.height = 100.00;

	//player values
	player = (Player){ 100, 785, 30, 30, 3, 1, {0, 0} };
	health = 3;
	
	
	
}


void Levelone_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	dt = CP_System_GetDt();//date time function
	//drawGrapple(&player.x, &player.y, &grapple.x, &grapple.y, dt); //draw grapple
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player
	//draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	//draw all platforms
	draw_platform(platform_base);
	draw_platform(platform1);
	draw_platform(platform2);
	draw_platform(platform_goal);
	//draw healthbar (with background)
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);
	//draw hazard 
	draw_platform(hazard);
	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);//start basic movement 

	// Decrease cooldown time
	if (collisionCooldown > 0.0f) {
		collisionCooldown -= dt;
	}
	
	// Check for game over (player collision with hazard)
	if (c_rect_rect(player.x, player.y, player.width, player.height, hazard.x, hazard.y, hazard.width, hazard.height)) {
		
		// Apply elastic collision
		ApplyElasticCollision(&player, hazard, 1.f);
		// Reset on_ground and start cooldown
		player.on_ground = 0;
		collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		health -= 1;
		if (health == 0) {
			health = 3;
			CP_Engine_SetNextGameStateForced(Levelone_Init, Levelone_Update, Levelone_Exit);
			printf("next state updated");
		}
	}

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//draw text for start_goal when 
	if (AreCircles_GoalIntersecting(player.x, player.y, 30, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
		CP_Font_DrawTextBox("Get to the Goal!", 50, 675, 100);
	}
	//test for next level (this will be for goal function)
	if (AreCircles_GoalIntersecting(player.x, player.y, 30, goal_end.x, goal_end.y, goal_end.width, goal_end.height)) {
		CP_Font_DrawTextBox("Press N to head to next level!", 1500, 200, 100);
		if (CP_Input_KeyTriggered(KEY_N))
		{
			CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit); // next level using N
		}
	}

	if ((c_rect_rect(player.x, player.y, 30, 30, (CP_System_GetWindowWidth() / 2), 800.00, (CP_System_GetWindowWidth()), 10.00)) != FALSE) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}
	if ((c_rect_rect(player.x, player.y, 30, 30, platform1.x, platform1.y, platform1.width, platform1.height)) != FALSE) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}
	if ((c_rect_rect(player.x, player.y, 30, 30, platform2.x, platform2.y, platform2.width, platform2.height)) != FALSE) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}
	if ((c_rect_rect(player.x, player.y, 30, 30, platform_goal.x, platform_goal.y, platform_goal.width, platform_goal.height)) != FALSE) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}

	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}
	
	if (CP_Input_KeyTriggered(KEY_P)) {
		
	}
	
}



void Levelone_Exit(void)
{

}