#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"
#include "movement.h"
#include "collision_utils.h"
#include "game.h"


Player player = { 100, 700, 1,{0, 0},100 };
Grapple grapple = { 0, 0, 0 };

void Game_Init(void)
{
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
	CP_Graphics_DrawCircle(player.x, player.y, player.diameter);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 10.00);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, 400.00, CP_System_GetWindowWidth(), 10.00);

	if (c_rect_rect(player.x, player.y, 100, 100, (CP_System_GetWindowWidth() / 2), 800.00, (CP_System_GetWindowWidth()), 10.00 )) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}
	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}
	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);
	drawGrapple(&player.x, &player.y, &grapple.x, &grapple.y, dt);

}

void Game_Exit(void)
{

}