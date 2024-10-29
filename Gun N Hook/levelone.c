#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"

//initialize all platform structs
typedef struct platform {

	double x;
	double y;
	double width;
	double height;
	CP_Color platform_color;

} platform;

//initialize all goal structs
typedef struct goal {

	double x;
	double y;
	double width;
	double height;
	double degrees;
	double corner_radius;
	CP_Color goal_color;

}goal;

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


platform platform_base, platform1, platform2, platform_goal;
goal goal_start, goal_end;



void Levelone_Init(void)
{
	//set all platform color as the same(dark red)
	platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);
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
	
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}

}

void Levelone_Exit(void)
{

}