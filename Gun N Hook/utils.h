/* file:	utils.h
// author:	Stanley Lur
// email: peihaostanley.lur@digipen.edu
// co-author: Amzar
// email: 
// brief:	This header file contains declarations for functions 
// used in collision detection, drawing, UI management,
// and gameplay mechanics for the game.These utilities
// provide core functionality for handling player
// interactions, rendering, and physics - based calculations.
// 
// Copyright ? 2020 DigiPen, All rights reserved.
//--------------------------------------------------------- */

#pragma once
#define NUM_BOSS_PARTS 9
#define MAX_HEALTH 5
#include "structs.h"



// ========================
// Collision Detection
// ========================
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreC_RIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height);

// ========================
// Drawing Functions
// ========================
void draw_platform(Platform platform);
void draw_goal(Goal goal);
void draw_healthbar(Healthbar healthbar);
void draw_boss(Boss* boss);
void draw_hearts(heart heart[], int current_hp);

// ========================
// UI and Menu Management
// ========================
void levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);
void pause_state(int* game_state);
void pause_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);
void restart_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);
void win_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);

// ========================
// Physics and Gameplay Mechanics
// ========================
void ApplyElasticCollision(Player* player, MELEE_Enemy hazard, float speed);
void update_boss_healthbar(Healthbar* health_bar, int current_health);
