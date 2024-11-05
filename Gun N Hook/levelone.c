#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "leveltwo.h"




platform platform_base, platform1, platform2, platform_goal;
goal goal_start, goal_end;
healthbar player_health, player_health_background;
float circleX;
float circleY;
float circleDiameter;
CP_Color red;

void Levelone_Init(void)
{
	red = CP_Color_Create(255, 0, 0, 255);
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);
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
	//
	 circleX = goal_start.x;
	 circleY = goal_start.y;
	 circleDiameter = 30;
}


void Levelone_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
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
	
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//test for next level (this will be for goal function)
	if (CP_Input_KeyTriggered(KEY_N))
	{
		CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit); // next level using N
	}
	CP_Settings_Fill(red);
	CP_Graphics_DrawCircle(circleX, circleY, circleDiameter);

	if (CP_Input_KeyDown(KEY_W)) { //move up, when move up y--
		//movement
		circleY -= 5;
	}// end of check key W
	else if (CP_Input_KeyDown(KEY_A)) { //move left when move left x--
		//movement
		circleX -= 5;
	} // end of check key A
	else if (CP_Input_KeyDown(KEY_S)) { //move down when move down y++
		//movement
		circleY += 5;
	} // end of check key S
	else if (CP_Input_KeyDown(KEY_D)) { //move right when move right x++
		//movement
		circleX += 5;
	} // end of check key D


}

void Levelone_Exit(void)
{

}