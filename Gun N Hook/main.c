//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include "game.h"
#include "enemy.h"
#include "levelboss.h"

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	//CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
	CP_Engine_SetNextGameState(Enemy_Init, Enemy_Update, Enemy_Exit);
	//CP_Engine_SetNextGameState(Levelboss_Init, Levelboss_Update, Levelboss_Exit);
	//CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run(1);
	return 0;
}
