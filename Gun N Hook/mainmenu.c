#include "cprocessing.h"


#include "levelselect.h"
#include "credit.h"
//hi
#include <stdio.h>
#include "utils.h"
#include "levelone.h"
#include "structs.h"

CP_Font myFont;
float textSize;


void Main_Menu_Init(void)
{
    textSize = 50.0f;
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    CP_Settings_TextSize(textSize);
}

void Main_Menu_Update(void)
{
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

    // set the background color to gray
    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

    // set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // draw a rectangle for the play button
    buttoncreate(xRect, yRect1, rectW, rectH,Blue);
    textwrite("Play", xRect, yRect1, Black);
    
    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_SetNextGameState(Levelone_Init, Levelone_Update, Levelone_Exit);
        };
    };

    // draw a rectangle for the credit button
    buttoncreate(xRect, yRect2, rectW, rectH, Blue);
    textwrite("Credit", xRect, yRect2, Black);

    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_SetNextGameState(Credit_Init, Credit_Update, Credit_Exit);
        };
    };



    // draw a rectangle for the exit button
    buttoncreate(xRect, yRect3, rectW, rectH, Blue);
    textwrite("Exit", xRect, yRect3, Black);

    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect3, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_Terminate();
        };
    };

    
}

void Main_Menu_Exit(void)
{

}