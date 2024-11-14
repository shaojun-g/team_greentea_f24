#include "cprocessing.h"
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
    float xRect = CP_System_GetWindowWidth() / 2.0f;
    float yRect1 = CP_System_GetWindowHeight() / 4.0f;
    float yRect2 = CP_System_GetWindowHeight() / 1.4f;
    float rectW = CP_System_GetWindowWidth() / 5.0f;
    float rectH = CP_System_GetWindowHeight() / 5.0f;

    // set the background color to gray
    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

    // set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // draw a rectangle at the center of the screen
    CP_Settings_Fill(CP_Color_Create(0, 200, 255, 255));
    CP_Graphics_DrawRect(xRect, yRect1,
        rectW, rectH);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Play", CP_System_GetWindowWidth() / 2.1f, CP_System_GetWindowHeight() / 3.75f);
    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect1, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_SetNextGameState(Levelone_Init, Levelone_Update, Levelone_Exit);
        };
    };

    // draw a rectangle at the center of the screen
    CP_Settings_Fill(CP_Color_Create(0, 200, 255, 255));
    CP_Graphics_DrawRect(xRect, yRect2,
        rectW, rectH);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Exit", CP_System_GetWindowWidth() / 2.1f, CP_System_GetWindowHeight() / 1.36f);
    if (CP_Input_MouseClicked()) {
        if (IsAreaClicked(xRect, yRect2, rectW, rectH, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
            CP_Engine_Terminate();
        };
    };
}

void Main_Menu_Exit(void)
{

}