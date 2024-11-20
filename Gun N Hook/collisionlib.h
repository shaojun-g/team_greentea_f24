#pragma once
#include "utils.h"

void collide_platform(Player* player, Platform* platform);

void deal_damage(Bullet bullets[], float* char_x, float* char_y, float* char_width, float* char_height, int* char_HP);

int deal_damage_to_player(Bullet* projectile, RANGE_Enemy* rangenemy, Player* player);

void pea_shooter_init(Bullet bullets[], float* player_x, float* player_y);

void pea_shooter(Bullet bullets[], float* player_x, float* player_y);

