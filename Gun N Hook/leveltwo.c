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
#include "levelthree.h"


#define PLATFORM_SIZE 5
Platform platform_base, platform1, platform2, platform3, platform_goal;
Platform platform[PLATFORM_SIZE];
Player player;
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
float dt;

void Leveltwo_Init(void)
{
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform[0] = (Platform){ CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 15.00,CP_Color_Create(255, 128, 128, 255) };
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform[1] = (Platform){ 600.00 , 650.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform2 is second platform
	platform[2] = (Platform){ 800.00 , 500.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform3 is third platform
	platform[3] = (Platform){ 1000.00 , 350.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform[4] = (Platform){ 1475.00 , 200.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//start goal will be where user spawns
	goal_start.x = 100.00;
	goal_start.y = 765.00;
	goal_start.width = 40.00;
	goal_start.height = 70.00;
	goal_start.corner_radius = 10;
	//end goal will be where user goes to next map
	goal_end.x = 1550.00;
	goal_end.y = 165.00;
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

	//player values
	player = (Player){ 100, 785, 30, 30, 3, 1, {0, 0} };
	
}


void Leveltwo_Update(void)
{
	dt = CP_System_GetDt();//date time function
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	//draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	//draw all platforms
	//draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);

		if (c_rect_rect(player.x, player.y, player.width, player.height, platform[i].x, platform[i].y, platform[i].width, platform[i].height)) {
			player.velocity.y = 0;
			player.on_ground = 1;
		}
	}
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player
	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);//start basic movement 

	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}
	
	//draw healthbar (with background)
	//draw_healthbar(player_health_background);
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//test for next level (this will be for goal function)
	if (CP_Input_KeyTriggered(KEY_N))
	{
		CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit); // next level using N
	}

}

void Leveltwo_Exit(void)
{

}