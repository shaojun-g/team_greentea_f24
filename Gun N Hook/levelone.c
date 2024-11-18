
#include <stdio.h>
#include <stdbool.h>

#include "cprocessing.h"
#include "string.h"
#include "utils.h"
#include "levelone.h"
#include "mainmenu.h"
#include "player.h"
#include "collision_utils.h"
#include "health.h"

//player starting values
Player player;// = { 100, 700, 1,{0, 0} };


CP_Font myFont;
CP_Image FullHeart;
double textSize;


//heart coordinates
float heartwidth = 50.f;
float heartheight = 50.f;
float heartx = 30.f;
float hearty = 30.f;
float spacing = 50.f;

//pointer for the number of hearts
int* size = 3;
bool game_running = true;
int x;

 

void Level_1_Init(void) {
    textSize = 50.0f;
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	FullHeart = CP_Image_Load("Assets/heart.png");
    CP_Settings_TextSize(textSize);

	player = (Player){ 100, 700, 1,{0, 0} };

}

void Level_1_Update(void) {
	heart fullheart[100] = {
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 1
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 2
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 3
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 4
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 5
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 6
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 7
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 8
		{FullHeart,heartx, hearty, heartwidth, heartheight},  // Heart 9
		{FullHeart,heartx, hearty, heartwidth, heartheight}   // Heart 10
	};


	// set rectangle x & y position 
	double xRect = CP_System_GetWindowWidth() / 2.0f;
	double yRect1 = CP_System_GetWindowHeight() / 4.6f;
	double yRect2 = CP_System_GetWindowHeight() / 1.9f;
	double yRect3 = CP_System_GetWindowHeight() / 1.2f;
	double rectW = CP_System_GetWindowWidth() / 4.4f;
	double rectH = CP_System_GetWindowHeight() / 4.4f;

	//colors used
	CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
	CP_Color White = CP_Color_Create(255, 255, 255, 255);
	CP_Color Black = CP_Color_Create(0, 0, 0, 255);


    //set background
    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	//width and height of the window
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();
	
	//heart coordinates
	fullheart[0].x = 30.f;

	//delta time
	double dt = CP_System_GetDt();
	if (game_running) {
		basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);
	}

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player.x, player.y, 100);

	

	///Draw Hearts
	draw_hearts(fullheart, &size);
	

	CP_Graphics_DrawRect(width / 2.0, 800.00, width, 10.00);
	CP_Graphics_DrawRect(width / 2.0, 400.00, width, 10.00);

	//Game Pause
	if (!game_running) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		CP_Graphics_DrawRect(width/2.0, height/2.0, width, height);
		
		//continue button
		buttoncreate(xRect, yRect1, rectW, rectH, Blue);
		textwrite("Continue", xRect, yRect1, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				game_running = pause_menu(game_running);

			}
		}

		// restart button
		buttoncreate(xRect, yRect2, rectW, rectH, Blue);
		textwrite("Restart", xRect, yRect2, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				game_running = pause_menu(game_running);
				CP_Engine_SetNextGameStateForced(Level_1_Init, Level_1_Update, Level_1_Exit);
			};
		};


		// exit button
		buttoncreate(xRect, yRect3, rectW, rectH, Blue);
		textwrite("Exit to main menu", xRect, yRect3, Black);

		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(xRect, yRect3, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				game_running = pause_menu(game_running);
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			};
		};


	}
	else {
		//CP_Settings_Tint(CP_Color_Create(0, 0, 0, 0));
	}

	

	if (c_rect_rect(player.x, player.y, 100, 100, (CP_System_GetWindowWidth() / 2.0), 800.00, (CP_System_GetWindowWidth()), 10.00)) {
		player.velocity.y = 0;
		player.on_ground = 1;
	}

	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}
	//return to main menu
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	//heart test
	if (CP_Input_KeyTriggered(KEY_H)) {
		remove_hearts(&size);

	}
	if (CP_Input_KeyTriggered(KEY_J)) {
		add_hearts(&size);

	}

	//pause menu
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		game_running = pause_menu(game_running);

	}
	if (CP_Input_KeyTriggered(KEY_G)) {

		 CP_Engine_SetNextGameStateForced(Level_1_Init, Level_1_Update, Level_1_Exit);
	}
	
	//end program
	if (CP_Input_KeyTriggered(KEY_R))
	{
		CP_Engine_Terminate();
	}

}

void Level_1_Exit(void) {

}