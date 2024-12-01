/* file:	mainmenu.c
// author:	Muhamad Amzar Bin Mohamad Zamre
// email:	muhamadamzar.b@digipen.edu
// work done: wrote a button create function 
// and a glow hover function. implemented all the button functions
// and the reset function
//
//
// brief:	This file contains the implementation for
// levelselect.c.
//
//
// Copyright @ 2020 DigiPen, All rights reserved.
//--------------------------------------------------------- */



#include "cprocessing.h"

#include <stdio.h>
#include <stdlib.h>
#include "levelselect.h"
#include "credit.h"
#include "utils.h"
#include "levelthree.h"
#include "structs.h"
#include "levelone.h"
#include "save.h"

#define MAX_LEVEL 4

CP_Font myFont;
float textSize;





void Main_Menu_Init(void)
{
    // set rectangle x & y position 
    textSize = 50.0f;
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    CP_Settings_TextSize(textSize);
    
}

void Main_Menu_Update(void)
{
    float width = CP_System_GetWindowWidth() / 1.0f;
    float height = CP_System_GetWindowHeight()/ 1.0f;
    float xRect = CP_System_GetWindowWidth() / 3.8f;
    float xRect1 = CP_System_GetWindowWidth() / 2.0f;
    float xRect2 =  CP_System_GetWindowWidth() / 1.35f;
    float yRect = CP_System_GetWindowHeight() / 1.2f;
    float yRect1 = CP_System_GetWindowHeight() / 3.f;
    float rectW = CP_System_GetWindowWidth() / 6.4f;
    float rectH = CP_System_GetWindowHeight() / 6.4f;

    //colors used
    CP_Color Blue = CP_Color_Create(0, 200, 255, 255);
    CP_Color White = CP_Color_Create(255, 255, 255, 255);
    CP_Color Black = CP_Color_Create(0, 0, 0, 255);

    // set the background color to gray
    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

    // set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    //Main Title Screen
    CP_Settings_TextSize(200.f);
    textwrite("Gun n Hook", xRect1 + 10.f, yRect1 + 10.f, Black);
    CP_Settings_TextSize(200.f);
    textwrite("Gun n Hook", xRect1, yRect1, White);

    //file name allocation
    char str[100] = "Assets/Save_File/level_1.txt";


    // draw a rectangle for the play button
    CP_Settings_TextSize(50.f);
    buttoncreate(xRect, yRect, rectW, rectH,Blue);
    textwrite("Start Game", xRect, yRect, Black);

    
    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update,Level_Select_Exit);
        };
    };

   

    // draw a rectangle for the credit button
    CP_Settings_TextSize(50.f);
    buttoncreate(xRect1, yRect, rectW, rectH, Blue);
    textwrite("Controls/", xRect1, yRect- 25.f, Black);
    textwrite("Credits", xRect1, yRect + 25.f, Black);


    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect1, yRect, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
           
            CP_Engine_SetNextGameState(Credit_Init, Credit_Update, Credit_Exit);
        };
    };



    // draw a rectangle for the exit button
    buttoncreate(xRect2, yRect, rectW, rectH, Blue);
    textwrite("Exit", xRect2, yRect, Black);

    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect2, yRect, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            for (int i = 0; i < MAX_LEVEL; ++i) {
                str[23] = '1' + i;
                level_reset(str);
            }
            CP_Engine_Terminate();
        };
    };

    // draw a rectangle for the reset button
    CP_Settings_TextSize(35.f);
    buttoncreate(width - 100.f, height - 30.f, rectW - 50.f, rectH - 50.f, Blue);
    textwrite("Reset Save", width - 100.f, height - 30.f, Black);


    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(width - 100.f, height - 30.f, rectW - 50.f, rectH - 50.f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            for (int i = 0; i < MAX_LEVEL; ++i) {
                str[23] = '1' + i;
                level_reset(str);
            }
        };
    };

    CP_Settings_TextSize(50.f);
  
}

void Main_Menu_Exit(void)
{   
    

}