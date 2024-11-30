#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"
#include "credit.h"

CP_Font MenuFont;
float textSize;
int state;


void Credit_Init(void) {
	CP_System_SetWindowSize(1600, 900);
	MenuFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	state = 1;

}
void Credit_Update(void) {
	//set background color
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	//ellipse Settings
	float xelli = 100.f;
	float xelli2 = 1500.f;
	float yelli = 800.f;

	// Color Pool
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Color White = CP_Color_Create(255, 255, 255, 255);

	//center for Credit
	float xRect1 = CP_System_GetWindowWidth() / 3.f;
	float xRect2 = CP_System_GetWindowWidth() / 3.4f;
	float yRect1 = CP_System_GetWindowHeight() / 4.0f;

	//textwrite("Game Made By:\n Amzar\n Shao Jun \n Ben \n Kwan \n Stanley ",xRect1 , yRect1,);
	CP_Settings_Fill(White);
	CP_Graphics_DrawEllipse(xelli, yelli, 100.f, 100.f);
	CP_Settings_Fill(Black);
	CP_Font_DrawText("<<", xelli, yelli);

	
	CP_Settings_Fill(White);
	CP_Graphics_DrawEllipse(xelli2, yelli, 100.f, 100.f);
	CP_Settings_Fill(Black);
	CP_Font_DrawText(">>", xelli2, yelli);
	
	
	
	if (state == 1) {
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(70.f);
		CP_Settings_Fill(Black);
		CP_Font_DrawTextBox("Game Made By:\n Amzar\n Shao Jun \n Ben \n Kwan \n Stanley", xRect1, yRect1, 500.f);

		if (IsCircleClicked(xelli, yelli, 100.f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			if (CP_Input_MouseClicked()) {

				state = 0;
			}
		}
	}

	if (state == 0) {
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(70.f);
		CP_Settings_Fill(Black);
		CP_Font_DrawTextBox("Game Controls:\n Movement: WASD \n Jump: W \n Grapple: Right Click \n Peashooter: Left Click", xRect2, yRect1, 600.f);

		if (IsCircleClicked(xelli2, yelli, 100.f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			if (CP_Input_MouseClicked()) {

				state = 1;
			}
		}

	}

	if (CP_Input_KeyTriggered(KEY_RIGHT) || CP_Input_KeyTriggered(KEY_D)) {
		state = !state;
	}

	if (CP_Input_KeyTriggered(KEY_LEFT) || CP_Input_KeyTriggered(KEY_A)) {
		state = !state;
	}

	if (CP_Input_KeyTriggered(KEY_Q) || CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

}
void Credit_Exit(void) {





}