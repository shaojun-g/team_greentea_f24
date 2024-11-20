#pragma once
#define NUM_BOSS_PARTS 9
#define MAX_HEALTH 5
#include "structs.h"





//initialize all goal structs





void levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);

//button functions
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);

//pause functions
void pause_state(int* game_state);
void pause_menu(int *game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);
void restart_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);
void win_menu(int* game_state, FunctionPtr currentlevel_init, FunctionPtr currentlevel_update, FunctionPtr currentlevel_exit);
float collisionCooldown;  // Cooldown timer for on_ground reset
float collisionCooldownDuration; // Duration in seconds for cooldown
//define dt as time
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

//all used funct
int AreC_RIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height);
void draw_platform(Platform platform);
void draw_goal(Goal goal);
void draw_boss(Boss* boss);
void ApplyElasticCollision(Player* player, MELEE_Enemy hazard, float restitution);


int check_collision_rect(float proj_x, float proj_y, float proj_diameter, float player_x, float player_y, float player_width, float player_height);
void update_projectile(Projectile* projectile, float player_x, float player_y, float player_width, float player_height, int* player_hp);
void update_boss_healthbar(Healthbar* health_bar, int current_health);

void draw_hearts(heart heart[], int current_hp);

