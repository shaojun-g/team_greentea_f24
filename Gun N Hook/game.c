#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"
#include "movement.h"
#include "collision_utils.h"
#include "game.h"



Player player1;
Grapple grapple1 = { 0, 0, 0 };

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
	CP_Graphics_DrawCircle(player1.x, player1.y, 10);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 10.00);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, 400.00, CP_System_GetWindowWidth(), 10.00);

	if (c_rect_rect(player1.x, player1.y, 100, 100, (CP_System_GetWindowWidth() / 2), 800.00, (CP_System_GetWindowWidth()), 10.00 )) {
		player1.velocity.y = 0;
		player1.on_ground = 1;
	}
	if (player1.on_ground != 1) {
		gravity(&player1.y, &player1.velocity.y, dt);
	}
	basic_movement(&player1.x, &player1.y, &player1.velocity.x, &player1.velocity.y, &player1.on_ground, dt);
	drawGrapple(&player1.x, &player1.y, &grapple1.x, &grapple1.y, dt);

}

void Game_Exit(void)
{

}