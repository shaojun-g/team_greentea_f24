#include "cprocessing.h" // Must have
#include "mainmenu.h"

float LogoOpacity;
float fadespeed_outwards;
CP_Image digipen_logo;

void InitialSplash_Init(void) {
    LogoOpacity = 255.0f;
    fadespeed_outwards = 85.0f;
    digipen_logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
}

void InitialSplash_Update(void) {
    //Background Color
    CP_Color Black = CP_Color_Create(0, 0, 0, 255);
    CP_Graphics_ClearBackground(Black);

    CP_Settings_ImageMode(CP_POSITION_CENTER); // Mode for drawing image
    CP_Image_Draw(digipen_logo, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f,
        762.5f, 222.5f, LogoOpacity);

    // Fade out logo after 3 seconds
    if (LogoOpacity > 0.0f) {
        LogoOpacity -= fadespeed_outwards * CP_System_GetDt();
        if (LogoOpacity < 0.0f) {
            LogoOpacity = 0.0f;
            CP_Engine_SetNextGameState(Main_Menu_Init ,Main_Menu_Update, Main_Menu_Exit);
        }
    }

    if (CP_Input_MouseClicked()) {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void InitialSplash_Exit(void) {
    CP_Image_Free(&digipen_logo);
}