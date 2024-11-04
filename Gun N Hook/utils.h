#pragma once

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
int levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);