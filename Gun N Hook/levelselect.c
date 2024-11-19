#include <stdio.h>
#include <CProcessing.h>
#include <stdbool.h>

#include "levelselect.h"
#include "mainmenu.h"
#include "utils.h"
#include "levelone.h"
#include "save.h"


CP_Font MenuFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

struct Button
{
	float xPos;
	float yPos;
	float height;
	float width;
	CP_Color color;
};

float timer;
bool level_1, level_2, level_3, level_4, level_5;


void Level_Select_Init(void)
{
	CP_System_SetWindowSize(1600, 900);
	MenuFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	timer = 0;



}


void Level_Select_Update(void) {
	
	//colors used
	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Color Red = CP_Color_Create(255, 200, 200, 255);

	timer += CP_System_GetDt();

	//Save State Check
	if (timer < 1.3f && timer > .3f) {
		if (!progress_check("Assets/Save_File/level_1.txt") || !progress_check("Assets/Save_File/level_2.txt") || !progress_check("Assets/Save_File/level_3.txt") || !progress_check("Assets/Save_File/level_4.txt") || !progress_check("Assets/Save_File/level_5.txt")) {
			CP_Settings_Fill(Red);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Graphics_DrawRect(CP_System_GetWindowHeight() / 1.13f, CP_System_GetWindowHeight() / 1.98f, CP_System_GetWindowWidth() / 2.8f, CP_System_GetWindowHeight() / 8.0f);
			CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
			textwrite("Save File could not be read", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, Black);
		}
		else {
			CP_Settings_Fill(Red);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Graphics_DrawRect(CP_System_GetWindowHeight() / 1.13f, CP_System_GetWindowHeight() / 1.98f, CP_System_GetWindowWidth() / 4.3f, CP_System_GetWindowHeight() / 8.0f);
			CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
			textwrite("Save File loaded", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, Black);
		}
		
		
		CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	}
	
	

	//set background color
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));


	//rectangle x coordinates
	double xRect3 = CP_System_GetWindowWidth() / 1.2f;
	double xRect2 = CP_System_GetWindowWidth() / 2.0f;
	double xRect1 = CP_System_GetWindowWidth() / 5.8f;
	double xRect4 = CP_System_GetWindowWidth() / 3.0f;
	double xRect5 = CP_System_GetWindowWidth() / 1.5f;

	//rectangle y coordinates
	double yRect1 = CP_System_GetWindowHeight() / 4.0f;
	double yRect2 = CP_System_GetWindowHeight() / 1.4f;

	//rectangle width and height
	double rectW = CP_System_GetWindowWidth() / 4.4f;
	double rectH = CP_System_GetWindowHeight() / 4.4f;



	//Level Clear State
	//if (progress_check("save_file/level_1.txt"));


	// draw a rectangle of level_1_select
	buttoncreate(xRect1, yRect1, rectW, rectH, Blue);
	textwrite("Level 1", xRect1, yRect1, Black);

	// draw a rectangle of level_2_select
	buttoncreate(xRect2, yRect1, rectW, rectH, Blue);
	textwrite("Level 2", xRect2, yRect1, Black);

	// draw a rectangle of level_3_select
	buttoncreate(xRect3, yRect1, rectW, rectH, Blue);
	textwrite("Level 3", xRect3, yRect1, Black);

	// draw a rectangle of level_4_select
	buttoncreate(xRect4, yRect2, rectW, rectH, Blue);
	textwrite("Level 4", xRect4, yRect2, Black);

	// draw a rectangle of level_5_select
	buttoncreate(xRect5, yRect2, rectW, rectH, Blue);
	textwrite("Level 5", xRect5, yRect2, Black);


	//level select
	//level 1
	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(xRect1, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Engine_SetNextGameState(Levelone_Init, Levelone_Update, Levelone_Exit);
			};
		};
		//level 2
		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect2, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				//CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update, Level_Select_Exit);
			};
		};
		//level 3
		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect3, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				//CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update, Level_Select_Exit);
			};
		};
		//level 4
		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect4, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				//CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update, Level_Select_Exit);
			};
		};
		//level 5
		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect5, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				//CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update, Level_Select_Exit);
			};
		};



		//return to main menu
	if (CP_Input_KeyTriggered(KEY_Q))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
		//end program
	if (CP_Input_KeyTriggered(KEY_R))
		{
			CP_Engine_Terminate();
		}


}


void Level_Select_Exit(void) {
	timer = 0;




}