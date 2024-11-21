#include "stdio.h"
#include "stdbool.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "leveltwo.h"
#include "levelone.h"
#include "collision_utils.h"
#include "collisionlib.h"
#include "movement.h"
#include "enemy.h"

#define PLATFORM_SIZE 4



//MELEE_Enemy hazard;
Platform platform[PLATFORM_SIZE];
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
Player player;
Grapple grapple;
heart player_healthbar[MAX_HEALTH];

float dt;
float elapsed_time; 
int is_paused;
int* game_state;

void Levelone_Init(void)
{
	CP_System_SetFrameRate(60.0f);		//	limit to 60fps
	//draw hearts
	for (int i = 0; i < MAX_HEALTH; ++i) {
		player_healthbar[i].heart = CP_Image_Load("./Assets/Heart.png");
		player_healthbar[i].x = 50.0f;  // Starting x position
		player_healthbar[i].y = 50.0f;  // Starting y position
		player_healthbar[i].width = 40.0f;  // Adjust as needed
		player_healthbar[i].height = 40.0f;  // Adjust as needed
	}
	CP_TEXT_ALIGN_HORIZONTAL h_text = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL v_text = CP_TEXT_ALIGN_V_MIDDLE;
	elapsed_time = 0;
	//Set font size for all goal texts
	CP_Settings_TextSize(25.00f);
	CP_Settings_TextAlignment(h_text, v_text);
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	
	//platform_base is the ground 
	platform[0] = (Platform){ CP_System_GetWindowWidth() / 2.0 , 800.00, CP_System_GetWindowWidth(), 15.00,CP_Color_Create(255, 128, 128, 255) };
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform[1] = (Platform){ 1000.00 , 650.00, 150.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform2 is second platform
	platform[2] = (Platform){ 1200.00 , 500.00, 150.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform[3] = (Platform){ 1475.00 , 350.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
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
	//player values
	player = (Player){ 100, 785, 30, 30, 5, 1, {0, 0} };
	grapple =(Grapple) { 0, 0, 0 };

	//pea-shooter init
	pea_shooter_init(bullets, &player.x, &player.y);

	//init pause state
	is_paused = 0;
	game_state = &is_paused;
}


void Levelone_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	dt = CP_System_GetDt();//date time function
	

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	DRAW
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	//	GRAPPLING HOOK FUNCTION
	drawGrapple(&player, &grapple.x, &grapple.y, platform, PLATFORM_SIZE, dt); //draw grapple
	//draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);
		collide_platform(&player, &platform[i]);
	}

	if (!is_paused) {

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	PLAYER FUNCTIONS
		//-----------------------------------------------------------------------------------------------------------------------------------------//

		//	pea shooter function
		pea_shooter(bullets, &player.x, &player.y);

		//	player basic movement		-	WASD and jump
		basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground);//start basic movement
		//	When player not on ground	-	GRAVITY
		if (!(player.on_ground))
			gravity(&player.velocity.y);

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	GOAL INSTRUCTIONS
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	instructions for player start.
		if (AreC_RIntersecting(player.x, player.y, 30, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255)); // Black color
			CP_Font_DrawTextBox("Get to the Goal!", 50, 675, 100);
		}
		//	instructions for player to grapple.
		if (AreC_RIntersecting(player.x, player.y, 30, 925, goal_start.y, goal_start.width, goal_start.height)) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255)); // Black color
			CP_Font_DrawTextBox("Right click to grapple!", 850, 675, 100);
		}
		//	player reach goal point	-	print instructions.
		if (AreC_RIntersecting(player.x, player.y, 30, goal_end.x, goal_end.y, goal_end.width, goal_end.height)) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255)); // Black color
			CP_Font_DrawTextBox("Press N to head to next level!", 1500, 200, 100);
			if (CP_Input_KeyTriggered(KEY_N))
			{
				CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit); // next level using N
			}
		}
	}

	//draw player
	CP_Settings_Fill(CP_Color_Create(250, 250, 250, 255));
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	UI
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	draw_healthbar(player_health_background);
	draw_hearts(player_healthbar, player.HP);
	/*draw_healthbar(player_health_background);
	draw_healthbar(player_health);*/
	//	pause menu
	if (is_paused) {
		pause_menu(game_state, Levelone_Init, Levelone_Update, Levelone_Exit);
	}
	//	esc to pause game
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) 
	{
		pause_state(game_state);
	}
}

void Levelone_Exit(void)
{
	// Free heart images
	for (int i = 0; i < MAX_HEALTH; ++i) {
		CP_Image_Free(&player_healthbar[i].heart);
	}

}