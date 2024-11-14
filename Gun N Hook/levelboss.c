// file:	enemy.c
// author:	Stanley
// email:	
// co-author: Benjamin Ban
// email: k.ban@digipen.edu
// brief:	
// 
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "levelthree.h"
#include "enemy.h"


Platform platform_base, platform1, platform2, platform3, platform_goal;
goal goal_start, goal_end;
healthbar player_health, player_health_background, boss_health, boss_health_background;
boss boss1;

enum { NUM_BOSS_TURRETS = 4 };
RANGE_Enemy boss_turrets[NUM_BOSS_TURRETS];
enum { MAX_TURRET_PROJECTILE = 4 };
Projectile turret_projectiles[MAX_TURRET_PROJECTILE];
Player player1;
CP_Font my_awesome_font;
float elaspedTime;

void Levelboss_Init(void)
{
	int current_level = 4;
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform3.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);
	//set boss color
	boss1.num_parts = NUM_BOSS_PARTS;
	//parts 0 is body of the boss
	boss1.parts[0] = (Platform){ .x = 1500, .y = 397.5, .width = 200, .height = 795, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	//parts 1-2 is base platform canon
	boss1.parts[1] = (Platform){ .x = 1375, .y = 770, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[2] = (Platform){ .x = 1312.5, .y = 770, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 3-4 is first platform canon
	boss1.parts[3] = (Platform){ .x = 1375, .y = 622.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[4] = (Platform){ .x = 1312.5, .y = 622.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 5-6 is second platform canon
	boss1.parts[5] = (Platform){ .x = 1375, .y = 472.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[6] = (Platform){ .x = 1312.5, .y = 472.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 7-8 is third platform canon
	boss1.parts[7] = (Platform){ .x = 1375, .y = 322.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[8] = (Platform){ .x = 1312.5, .y = 322.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//init boss turret variables turret0=part2,1=4,2=6,3=8
	for (int i = 0; i < NUM_BOSS_TURRETS; i++) {
		boss_turrets[i].x = boss1.parts[(i + 1) * 2].x;
		boss_turrets[i].y = boss1.parts[(i + 1) * 2].y;
		boss_turrets[i].width = boss1.parts[(i + 1) * 2].width;
		boss_turrets[i].height = boss1.parts[(i + 1) * 2].height;
		boss_turrets[i].shoot_posX = boss_turrets[i].x;
		boss_turrets[i].shoot_posY = boss_turrets[i].y;
	}// end of for-loop
	//init projectiles variables
	for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
		turret_projectiles[i].x = boss_turrets[i].shoot_posX;
		turret_projectiles[i].y = boss_turrets[i].shoot_posY;
		turret_projectiles[i].diameter = 15;
		turret_projectiles[i].travelling = 0;
	}// end of for-loop
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	boss_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	boss_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform_base.x = CP_System_GetWindowWidth() / 2;
	platform_base.y = 800.00;
	platform_base.width = CP_System_GetWindowWidth();
	platform_base.height = 10.00;
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform1.x = 600.00;
	platform1.y = 650.00;
	platform1.width = 250.00;
	platform1.height = 15.00;
	//platform2 is second platform
	platform2.x = 800.00;
	platform2.y = 500.00;
	platform2.width = 250.00;
	platform2.height = 15.00;
	//platform3 is third platform
	platform3.x = 1000.00;
	platform3.y = 350.00;
	platform3.width = 250.00;
	platform3.height = 15.00;
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	//platform_goal.x = 1475.00;
	//platform_goal.y = 200.00;
	//platform_goal.width = 250.00;
	//platform_goal.height = 15.00;
	//start goal will be where user spawns
	goal_start.x = 100.00;
	goal_start.y = 765.00;
	goal_start.width = 40.00;
	goal_start.height = 70.00;
	goal_start.corner_radius = 10;
	//end goal will be where user goes to next map
	//goal_end.x = 1550.00;
	//goal_end.y = 165.00;
	//goal_end.width = 40.00;
	//goal_end.height = 70.00;
	//goal_end.corner_radius = 10;
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
	//boss healthbar below base platform
	boss_health.x = 800.00;
	boss_health.y = 850;
	boss_health.width = 1400.00;
	boss_health.height = 75.00;
	//background of boss health
	boss_health.x = 800.00;
	boss_health.y = 850;
	boss_health.width = 1400.00;
	boss_health.height = 75.00;

	
}

void test_debug(void){

	//test debugging turret
	//player
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(140, 0, 0, 255));
	CP_Graphics_DrawRect(player1.x, player1.y, player1.width, player1.height);
	//movement
	if (CP_Input_KeyDown(KEY_A)) { //move left when move left x--
		//movement
		player1.x -= 5 + CP_System_GetDt();
	} // end of check key A
	else if (CP_Input_KeyDown(KEY_D)) { //move right when move right x++
		//movement
		player1.x += 5 + CP_System_GetDt();
	} // end of check key D
	//updown
	if (CP_Input_KeyDown(KEY_W)) { //move up when move left y--
		//movement
		player1.y -= 5 + CP_System_GetDt();
	} // end of check key A
	else if (CP_Input_KeyDown(KEY_S)) { //move down when move right y++
		//movement
		player1.y += 5 + CP_System_GetDt();
	} // end of check key D

	// Create an array of characters (aka a string) that can store up to 256 characters.
	char buffer[256];
	// Fill the buffer with the text we want.
	// Notice that it uses a similar syntax as printf()!
	sprintf_s(buffer, sizeof(buffer), "Player X: %.2f, Player: %.2f", player1.x, player1.y);
	// Tells CProcessing to use the white color for anything we are drawing on the screen
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	// Draw the text using the string stored in the buffer in the center of the screen.
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(buffer, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 - 300);
}

void Levelboss_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	//draw goals
	draw_goal(goal_start);
	//draw_goal(goal_end);
	//draw all platforms
	draw_platform(platform_base);
	draw_platform(platform1);
	draw_platform(platform2);
	draw_platform(platform3);
	//draw_platform(platform_goal);
	//draw boss
	draw_boss(&boss1);
	//draw projectile
	for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
		CP_Settings_EllipseMode(CP_POSITION_CENTER);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(turret_projectiles[i].x, turret_projectiles[i].y, turret_projectiles[i].diameter);
	}
	////
	//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	//CP_Graphics_DrawCircle(turret_projectiles[0].x_pos, turret_projectiles[0].y_pos, turret_projectiles[0].diameter);
	//CP_Graphics_DrawCircle(turret_projectiles[1].x_pos, turret_projectiles[1].y_pos, turret_projectiles[1].diameter);
	//CP_Graphics_DrawCircle(turret_projectiles[2].x_pos, turret_projectiles[2].y_pos, turret_projectiles[2].diameter);
	//CP_Graphics_DrawCircle(turret_projectiles[3].x_pos, turret_projectiles[3].y_pos, turret_projectiles[3].diameter);
	//draw healthbar (with background)
	//draw in update and update values of health during combat
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);
	draw_healthbar(boss_health);
	draw_healthbar(boss_health_background);
	
	

	for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
		if (turret_projectiles[i].travelling == 1) {
			enemy_shoot_projectile(&turret_projectiles[i], &boss_turrets[i], 300);
		}
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//test for next level (this will be for goal function)
	if (CP_Input_KeyTriggered(KEY_N))
	{
		CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit); // next level using N
	}
	//when boss is defeated, set a game over and credit scene

}

void Levelboss_Exit(void)
{

}