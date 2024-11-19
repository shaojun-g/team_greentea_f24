#pragma once
#define NUM_BOSS_PARTS 9
#include "structs.h"




//initialize all goal structs




int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
void levelselecthover(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);

//button functions
void buttoncreate(float area_center_x, float area_center_y, float area_width, float area_height, CP_Color color);
void textwrite(const char* text, float x_position, float y_position, CP_Color color);

//pause functions
int pause_menu(int state);
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
void Restart_Level();
void goal_function();
void ApplyElasticCollision(Player* player, MELEE_Enemy hazard, float restitution);


int check_collision_rect(float proj_x, float proj_y, float proj_diameter, float player_x, float player_y, float player_width, float player_height);
void update_projectile(Projectile* projectile, float player_x, float player_y, float player_width, float player_height, int* player_hp);
