#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"
#include "movement.h"
#include "collision_utils.h"


#define PLATFORM_SIZE 2
Player player1;
Grapple grapple1 = { 0, 0, 0 };

void Game_Init(void)
{
	player = (Player){ 500, 200, 1,{0, 0} };
	grapple = (Grapple){ 0, 0, 0 };
	platforms[0] = (platform){ CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 100.00,CP_Color_Create(255, 128, 128, 255)};
	platforms[1] = (platform){ CP_System_GetWindowWidth() / 2, 400.00, CP_System_GetWindowWidth()/4, 100.00, CP_Color_Create(255, 128, 128, 255)};
}

void Game_Update(void)
{
	float dt = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player1.x, player1.y, 10);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_NoStroke();
	//CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 10.00);
	//CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, 400.00, CP_System_GetWindowWidth(), 10.00);
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		CP_Settings_Fill(platforms[i].platform_color);
		CP_Graphics_DrawRect(platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height);

		if (c_rect_rect(player.x, player.y, 100, 100, platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height)) {
			player.velocity.y = 0;
			player.on_ground = 1;
		};
	}

	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}
	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);
	drawGrapple(&player.x, &player.y, &grapple.x, &grapple.y, &platforms, PLATFORM_SIZE, dt);

}

void Game_Exit(void)
{

}