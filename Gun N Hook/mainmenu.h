#pragma once

void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);

//button functions
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);

//level functions
void draw_platform(platform platform);
void draw_goal(goal goal);

//pause functions
int pause_menu(int state);