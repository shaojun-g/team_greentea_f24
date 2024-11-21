#include "cprocessing.h"


#include "levelselect.h"
#include "credit.h"
//hi
#include <stdio.h>
#include "utils.h"
#include "levelthree.h"
#include "structs.h"
#include "levelone.h"

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

    // draw a rectangle for the play button
    buttoncreate(xRect, yRect, rectW, rectH,Blue);
    textwrite("Play", xRect, yRect, Black);
    
    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_SetNextGameState(Level_Select_Init, Level_Select_Update,Level_Select_Exit);
        };
    };

    //Main Title Screen
    CP_Settings_TextSize(200.f);
    textwrite("Gun n Hook", xRect1 + 10.f, yRect1 + 10.f, Black);
    CP_Settings_TextSize(200.f);
    textwrite("Gun n Hook", xRect1, yRect1, White);

    // draw a rectangle for the credit button
    CP_Settings_TextSize(50.f);
    buttoncreate(xRect1, yRect, rectW, rectH, Blue);
    textwrite("Controls/", xRect1, yRect- 25.f, Black);
    textwrite("Credit", xRect1, yRect + 25.f, Black);


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
            CP_Engine_Terminate();
        };
    };

    
}

void Main_Menu_Exit(void)
{

}