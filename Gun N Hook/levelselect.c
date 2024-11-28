#include <stdio.h>
#include <CProcessing.h>
#include <stdbool.h>

#include "levelselect.h"
#include "mainmenu.h"
#include "utils.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelboss.h"
#include "save.h"

enum {LEVELNUM = 4};
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
int level_1 = 0, level_2 = 0, level_3 = 0, level_4 = 0; 


void Level_Select_Init(void)
{
	CP_System_SetWindowSize(1600, 900);
	MenuFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	timer = 0;

	level_1 = level_progress("Assets/Save_File/level_1.txt");
	level_2 = level_progress("Assets/Save_File/level_2.txt");
	level_3 = level_progress("Assets/Save_File/level_3.txt");
	level_4 = level_progress("Assets/Save_File/level_4.txt");
	char str[] = "Assets/Save_File/level_1.txt";

}


void Level_Select_Update(void) {

	//colors used
	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	//CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Color Green = CP_Color_Create(255, 200, 255, 255);
	CP_Color Red = CP_Color_Create(255, 200, 200, 255);

	//level button color
	CP_Color Levelone = Blue;
	CP_Color Leveltwo = Blue;
	CP_Color Levelthree = Blue;
	CP_Color Levelfour = Blue;
	
	

	//Level Clear State
	/*char str[] = "save_file/level_1.txt";
	char z = '1';
	for (int i = 0; i < (LEVELNUM - 1); ++i) {
		str[16] = (z + i);
		if (level_progress(str) == '1') {
			CP_Color temp = levels[i];
			CP_Color temp2 = colors_clear[i];
			temp = temp2;
			i++;
		}

	}*/
	
	


	timer += CP_System_GetDt();

	//Save State Check
	if (timer < 1.3f && timer > .3f) {
		if (!file_check("Assets/Save_File/level_1.txt") || !file_check("Assets/Save_File/level_2.txt") || !file_check("Assets/Save_File/level_3.txt") || !file_check("Assets/Save_File/level_4.txt") ) {
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
	float xRect3 = CP_System_GetWindowWidth() / 1.2f;
	float xRect2 = CP_System_GetWindowWidth() / 2.0f;
	float xRect1 = CP_System_GetWindowWidth() / 5.8f;
	float xRect4 = CP_System_GetWindowWidth() / 2.0f;
	float xRect5 = CP_System_GetWindowWidth() / 1.5f;

	//rectangle y coordinates
	float yRect1 = CP_System_GetWindowHeight() / 4.0f;
	float yRect2 = CP_System_GetWindowHeight() / 1.4f;

	//rectangle width and height
	float rectW = CP_System_GetWindowWidth() / 4.4f;
	float rectH = CP_System_GetWindowHeight() / 4.4f;


	//if ((IsAreaClicked(xRect1, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY()))) {
		if (level_1 == 1) {
			Levelone = Green;
			CP_Graphics_DrawRect(10, 10, 10, 10);
		}
		
		if (level_2 == 1) {
			Leveltwo = Green;
			CP_Graphics_DrawRect(10, 10, 10, 10);
		}
		if (level_3 == 1) {
			Levelthree = Green;
			CP_Graphics_DrawRect(10, 10, 10, 10);
		}
		if (level_4 == 1) {
			Levelfour = Green;
			CP_Graphics_DrawRect(10, 10, 10, 10);
		}
	//}
	
	


	// draw a rectangle of level_1_select
	buttoncreate(xRect1, yRect1, rectW, rectH, Levelone);
	textwrite("Level 1", xRect1, yRect1, Black);


	// draw a rectangle of level_2_select
	buttoncreate(xRect2, yRect1, rectW, rectH, Leveltwo);
	textwrite("Level 2", xRect2, yRect1, Black);

	// draw a rectangle of level_3_select
	buttoncreate(xRect3, yRect1, rectW, rectH, Levelthree);
	textwrite("Level 3", xRect3, yRect1, Black);

	// draw a rectangle of level_4_select
	buttoncreate(xRect4, yRect2, rectW, rectH, Levelfour);
	textwrite("Level 4", xRect4, yRect2, Black);

	//// draw a rectangle of level_5_select
	//buttoncreate(xRect5, yRect2, rectW, rectH, Blue);
	//textwrite("Level 5", xRect5, yRect2, Black);


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
			CP_Engine_SetNextGameState(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit);

				
		};
	};
	//level 3
	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(xRect3, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit);
		};
	};
	//level 4
	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(xRect4, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Levelboss_Init, Levelboss_Update, Levelboss_Exit);
		};
	};
		//level 5
		//if (CP_Input_MouseClicked()) {
		//	if (IsAreaClicked(xRect5, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		//		//CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update, Level_Select_Exit);
		//	};
		//};



		//return to main menu
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

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