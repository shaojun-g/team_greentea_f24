#include "stdio.h"
#include "mainmenu.h"

void Levelone_Init(void)
{
}


void Levelone_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Levelone_Exit(void)
{

}