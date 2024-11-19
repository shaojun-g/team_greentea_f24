#include <stdio.h>
#include <stdbool.h>

#include "cprocessing.h"
#include "utils.h"

//CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
//CP_Color White = CP_Color_Create(255, 255, 255, 255);
//CP_Color Black = CP_Color_Create(0, 0, 0, 255);

bool progress_check(const char *level) {
	FILE *check = fopen( level, "r");
	char letter;
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);
	CP_Color Red = CP_Color_Create(255, 200, 200, 255);

	if (!check) {
		/*CP_Settings_Fill(Red);
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(CP_System_GetWindowHeight() / 1.13f, CP_System_GetWindowHeight() / 1.98f, CP_System_GetWindowWidth() / 2.8f, CP_System_GetWindowHeight() / 8.0f );
		CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));*/
		perror("file does not exist/cannot be accessed");
/*		textwrite("Save File could not be read", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, Black)*/;
		return false;
	}
	
	if (check) {
		CP_Settings_Fill(Red);
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(CP_System_GetWindowHeight() / 1.13f, CP_System_GetWindowHeight() / 1.98f, CP_System_GetWindowWidth() / 4.3f, CP_System_GetWindowHeight() / 8.0f);
		CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
		textwrite("Save File loaded", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, Black);
		return true;

	}

	if (letter = fgetc(check) != EOF) {
		if (letter == 1);
			return true;
	}
	else {
		return false;
	}
	
}



bool level_clear(char const *goal) {
	FILE *open = fopen(goal, "r");
	
	if (!open) {
		perror("file does not exist/cannot be accessed");
		return false;
	}

	


}