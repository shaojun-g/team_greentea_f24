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

#define PLATFORM_SIZE 4



MELEE_Enemy hazard;
Platform platform[PLATFORM_SIZE];
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
Player player;
Grapple grapple;
collisionCooldown = 0.0f;  // Cooldown timer for on_ground reset
collisionCooldownDuration = 0.3f;  // Duration in seconds for cooldown
float dt;
float elapsed_time; 
int is_paused;
int* game_state;

void Levelone_Init(void)
{
	CP_TEXT_ALIGN_HORIZONTAL h_text = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL v_text = CP_TEXT_ALIGN_V_MIDDLE;
	elapsed_time = 0;
	//Set font size for all goal texts
	CP_Settings_TextSize(25.00f);
	CP_Settings_TextAlignment(h_text, v_text);
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
	
	drawGrapple(&player, &grapple.x, &grapple.y, platform, PLATFORM_SIZE, dt); //draw grapple

	draw_goal(goal_start);
	draw_goal(goal_end);

	//draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);
		collide_platform(&player, &platform[i]);
	}
	//draw goals

	//draw healthbar (with background)
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);
	////draw hazard 
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // Red color
	//CP_Graphics_DrawRect(hazard.x, hazard.y, hazard.width, hazard.height);

	
	if (!is_paused) {

		basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground);//start basic movement
		if (!(player.on_ground))
			gravity(&player.velocity.y);

		//pea shooter function
		pea_shooter(bullets, &player.x, &player.y);
	}
	//draw player
	CP_Settings_Fill(CP_Color_Create(250, 250, 250, 255));
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player

	// Decrease cooldown time
	if (collisionCooldown > 0.0f) {
		collisionCooldown -= dt;
	}
	
	if (is_paused) {
		pause_menu(game_state, Levelone_Init, Levelone_Update, Levelone_Exit);
	}
	// esc to pause game
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) 
	{
		pause_state(game_state);
	}

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//draw text for start_goal 
	if (AreC_RIntersecting(player.x, player.y, 30, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
		CP_Font_DrawTextBox("Get to the Goal!", 50, 675, 100);
	}
	//test for next level (this will be for goal function)
	if (AreC_RIntersecting(player.x, player.y, 30, goal_end.x, goal_end.y, goal_end.width, goal_end.height)) {
		CP_Font_DrawTextBox("Press N to head to next level!", 1500, 200, 100);
		if (CP_Input_KeyTriggered(KEY_N))
		{
			CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit); // next level using N
		}
	}
	
	
	if (CP_Input_KeyTriggered(KEY_P)) {
		
	}
	
}



void Levelone_Exit(void)
{

}