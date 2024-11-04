#include "cprocessing.h"
#include <stdio.h>;
#include "utils.h";
#include "mainmenu.h";
#include "credit.h";

//hi :3
CP_Font MenuFont;
double textSize;


void Credit_Init(void) {
	CP_System_SetWindowSize(1600, 900);
	MenuFont = CP_Font_Load("Assets/Exo2-Regular.ttf");

}
void Credit_Update(void) {
	//set background color
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	// Color Pool
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	
	//center for Credit
	double xRect1 = CP_System_GetWindowWidth() / 3.f;
	double yRect1 = CP_System_GetWindowHeight() / 4.0f;
	
	//textwrite("Game Made By:\n Amzar\n Shao Jun \n Ben \n Kwan \n Stanley ",xRect1 , yRect1, Black);
	CP_Graphics_DrawEllipse(100.f, 100.f, 100.f, 100.f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(70.f);
	CP_Font_DrawTextBox("Game Made By:\n Amzar\n Shao Jun \n Ben \n Kwan \n Stanley", xRect1, yRect1, 500);

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

}
void Credit_Exit(void) {





}