#pragma once
#define NUM_BOSS_PARTS 9
#include "structs.h"

float collisionCooldown;  // Cooldown timer for on_ground reset
float collisionCooldownDuration; // Duration in seconds for cooldown
//define dt as time
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

//all used funct
int AreCircles_GoalIntersecting(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_width, float rect_height);
void draw_platform(Platform platform);
void draw_goal(Goal goal);
void draw_boss(Boss* boss);
void Restart_Level();
void goal_function();
void ApplyElasticCollision(Player* player, MELEE_Enemy hazard, float restitution);