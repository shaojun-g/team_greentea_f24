#include "cprocessing.h"
#include <stdio.h>;
#include "utils.h";
#include "mainmenu.h"
#include "movement.h"

typedef struct {
	double x, y;  // x and y components of the velocity
} Velocity;

// Define a struct for Player
typedef struct {
	double x, y;  // x and y coordinates of the player position
	Velocity velocity;  // Nested struct for velocity
	int on_ground;
} Player;

Player player = { 100, 200,{300, 300} };


void Game_Init(void)
{

}

void Game_Update(void)
{
	double dt = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player.x, player.y, 100);
	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, dt);
}

void Game_Exit(void)
{

}