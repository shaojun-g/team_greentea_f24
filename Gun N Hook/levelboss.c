// file:	enemy.c
// author:	Stanley
// email:	
// co-author: Benjamin Ban
// email: k.ban@digipen.edu
// brief:	
// 
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

//increase projecctile size diameter++
//burst fire shoot 3x projectile

#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "levelthree.h"
#include "enemy.h"
#include "structs.h"
#include "movement.h"
#include "collision_utils.h"
#include "collisionlib.h"
#include "levelboss.h"
#include "save.h"

#define PLATFORM_SIZE 4

Platform platform[PLATFORM_SIZE];
Goal goal_start;
Healthbar player_health, player_health_background, boss_health, boss_health_background;
Player player;
Grapple grapple;
Boss boss1;
enum {NUM_MAX_MELEE = 5};
MELEE_Enemy melee_enemy[NUM_MAX_MELEE];
enum { NUM_BOSS_TURRETS = 4 };
RANGE_Enemy boss_turrets[NUM_BOSS_TURRETS];
enum { MAX_TURRET_PROJECTILE = 4 };
Bullet turret_projectiles[MAX_TURRET_PROJECTILE];
heart player_healthbar[MAX_HEALTH];

int is_paused, is_dead, boss_dead;
float dt, elapsedtime; float iframe_cd, iframe_dur;
int* game_state;

void Levelboss_Init(void)
{
	CP_System_SetFrameRate(60.0f);		//	limit to 60fps
	CP_Settings_TextSize(25.00f); // set text size to 25.0f
	int current_level = 4;
	//game window size is (1600, 900)
	boss1.num_parts = NUM_BOSS_PARTS;
	//parts 0 is body of the boss
	boss1.parts[0] = (Platform){ .x = 1500, .y = 397.5, .width = 200, .height = 795, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	//parts 1-2 is base platform canon
	boss1.parts[1] = (Platform){ .x = 1375, .y = 770, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[2] = (Platform){ .x = 1312.5, .y = 770, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 3-4 is first platform canon
	boss1.parts[3] = (Platform){ .x = 1375, .y = 622.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[4] = (Platform){ .x = 1312.5, .y = 622.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 5-6 is second platform canon
	boss1.parts[5] = (Platform){ .x = 1375, .y = 472.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[6] = (Platform){ .x = 1312.5, .y = 472.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//parts 7-8 is third platform canon
	boss1.parts[7] = (Platform){ .x = 1375, .y = 322.5, .width = 50, .height = 30, .platform_color = CP_Color_Create(140, 0, 0, 255) };
	boss1.parts[8] = (Platform){ .x = 1312.5, .y = 322.5, .width = 75, .height = 15, .platform_color = CP_Color_Create(0, 0, 0, 255) };
	//set boss health
	boss1.health = 50;
	//init boss turret variables turret0=part2,1=4,2=6,3=8
	for (int i = 0; i < NUM_BOSS_TURRETS; i++) {
		boss_turrets[i].x = boss1.parts[(i + 1) * 2].x;
		boss_turrets[i].y = boss1.parts[(i + 1) * 2].y;
		boss_turrets[i].width = boss1.parts[(i + 1) * 2].width;
		boss_turrets[i].height = boss1.parts[(i + 1) * 2].height;
		boss_turrets[i].shoot_posX = boss_turrets[i].x;
		boss_turrets[i].shoot_posY = boss_turrets[i].y;
	}// end of for-loop
	//init projectiles variables
	for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
		turret_projectiles[i].x = boss_turrets[i].shoot_posX;
		turret_projectiles[i].y = boss_turrets[i].shoot_posY;
		turret_projectiles[i].diameter = 15;
		turret_projectiles[i].live = 0;
	}// end of for-loop
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	boss_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	boss_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform[0] = (Platform){ CP_System_GetWindowWidth() / 2.0f , 800.00, CP_System_GetWindowWidth(), 10.00f,CP_Color_Create(255, 128, 128, 255) };
	platform[0].left_limit = platform[0].x - platform[0].width / 2;
	platform[0].right_limit = platform[0].x + platform[0].width / 2;
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform[1] = (Platform){ 400.00 ,  650.00, 250.00, 15.00,CP_Color_Create(255, 128, 128, 255) };
	platform[1].left_limit = platform[1].x - platform[1].width / 2;
	platform[1].right_limit = platform[1].x + platform[1].width / 2;
	//platform2 is second platform
	platform[2] = (Platform){ 600.00 ,  500.00, 250.00, 15.00,CP_Color_Create(255, 128, 128, 255) };
	platform[2].left_limit = platform[2].x - platform[2].width / 2;
	platform[2].right_limit = platform[2].x + platform[2].width / 2;
	//platform3 is third platform
	platform[3] = (Platform){ 500.00 ,  350.00, 250.00, 15.00,CP_Color_Create(255, 128, 128, 255) };
	platform[3].left_limit = platform[3].x - platform[3].width / 2;
	platform[3].right_limit = platform[3].x + platform[3].width / 2;
	//start goal will be where user spawns
	goal_start.x = 100.00;
	goal_start.y = 765.00;
	goal_start.width = 40.00;
	goal_start.height = 70.00;
	goal_start.corner_radius = 10;
	//player healthbar at top of map (will be rendered over everything else)
	player_health.x = 200.00;
	player_health.y = 50.00;
	player_health.width = 300.00;
	player_health.height = 20.00;
	//background of player healthbar
	player_health_background.x = 200.00;
	player_health_background.y = 50.00;
	player_health_background.width = 300.00;
	player_health_background.height = 20.00;
	//boss healthbar below base platform
	boss_health.x = 800.00;
	boss_health.y = 850;
	boss_health.width = 1400.00;
	boss_health.height = 75.00;
	//background of boss health
	boss_health.x = 800.00;
	boss_health.y = 850;
	boss_health.width = 1400.00;
	boss_health.height = 75.00;
	//initialize melee enemy 
	melee_enemy[0].width = 40;
	melee_enemy[0].height = 40;
	melee_enemy[0].x = platform[0].x;
	melee_enemy[0].y = platform[0].y - platform[0].height / 2 - melee_enemy[0].height / 2; // Place enemy just above platform
	melee_enemy[0].state = PATROL; // Start in patrol state
	melee_enemy[0].dir = RIGHT;
	melee_enemy[0].speed = 100;
	melee_enemy[0].health = 5;
	//initialize melee enemy 2
	melee_enemy[1].width = 40;
	melee_enemy[1].height = 40;
	melee_enemy[1].x = platform[1].x;
	melee_enemy[1].y = platform[1].y - platform[1].height / 2 - melee_enemy[1].height / 2; // Place enemy just above platform
	melee_enemy[1].state = PATROL; // Start in patrol state
	melee_enemy[1].dir = RIGHT;
	melee_enemy[1].speed = 100;
	melee_enemy[1].health = 5;
	//initialiize melee enemy 3
	melee_enemy[2].width = 40;
	melee_enemy[2].height = 40;
	melee_enemy[2].x = platform[2].x;
	melee_enemy[2].y = platform[2].y - platform[2].height / 2 - melee_enemy[2].height / 2; // Place enemy just above platform
	melee_enemy[2].state = PATROL; // Start in patrol state
	melee_enemy[2].dir = RIGHT;
	melee_enemy[2].speed = 100;
	melee_enemy[2].health = 5;
	//initializse melee enemy 4
	melee_enemy[3].width = 40;
	melee_enemy[3].height = 40;
	melee_enemy[3].x = platform[3].x;
	melee_enemy[3].y = platform[3].y - platform[3].height / 2 - melee_enemy[3].height / 2; // Place enemy just above platform
	melee_enemy[3].state = PATROL; // Start in patrol state
	melee_enemy[3].dir = RIGHT;
	melee_enemy[3].speed = 100;
	melee_enemy[3].health = 5;
	//initialize melee enemy 5 to stop player from staying on level one
	melee_enemy[4].width = 40;
	melee_enemy[4].height = 40;
	melee_enemy[4].x = platform[0].x -200;
	melee_enemy[4].y = platform[0].y - platform[0].height / 2 - melee_enemy[0].height / 2; // Place enemy just above platform
	melee_enemy[4].state = PATROL; // Start in patrol state
	melee_enemy[4].dir = RIGHT;
	melee_enemy[4].speed = 170;
	melee_enemy[4].health = 5;
	//initialize player
	player = (Player){ 100, 785, 30, 30, 5, 1, {0, 0} };
	grapple = (Grapple){ 0, 0, 0 };
	elapsedtime = 0;  iframe_dur = 0.5f, iframe_cd = 0.0f;
	// Initialize heart array
	for (int i = 0; i < MAX_HEALTH; ++i) {
		player_healthbar[i].heart = CP_Image_Load("./Assets/Heart.png");
		player_healthbar[i].x = 50.0f;  // Starting x position
		player_healthbar[i].y = 50.0f;  // Starting y position
		player_healthbar[i].width = 40.0f;  // Adjust as needed
		player_healthbar[i].height = 40.0f;  // Adjust as needed
	}
	//pea-shooter init
	pea_shooter_init(bullets, &player.x, &player.y);

	//win state
	boss_dead = 0;
	//death state
	is_dead = 0;
	//pause state
	is_paused = 0;
	game_state = &is_paused;
	
	
}


void Levelboss_Update(void)
{
	dt = CP_System_GetDt();//date time function
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	DRAW
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	draw goal
	draw_goal(goal_start);

	//	draw melee enemy
	for (int i = 0; i < NUM_MAX_MELEE; i++) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(melee_enemy[i].x, melee_enemy[i].y, melee_enemy[i].width, melee_enemy[i].height);
	}

	//	draw enemy projectiles
	for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
		CP_Settings_EllipseMode(CP_POSITION_CENTER);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(turret_projectiles[i].x, turret_projectiles[i].y, turret_projectiles[i].diameter);
	}
	//	GRAPPLING HOOK FUNCTION
	drawGrapple(&player, &grapple.x, &grapple.y, platform, PLATFORM_SIZE, dt); //draw grapple

	//	draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);
		collide_platform(&player, &platform[i]);
	}

	if (!is_paused) {
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	PLAYER FUNCTIONS
		//-----------------------------------------------------------------------------------------------------------------------------------------//

		//	pea shooter function
		pea_shooter(bullets, &player.x, &player.y);

		//	deal damage to enemies
		deal_damage(bullets, &boss1.parts->x, &boss1.parts->y, &boss1.parts->width, &boss1.parts->height, &boss1.health);

		//	player basic movement		-	WASD and jump
		basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground);
		//	When player not on ground	-	GRAVITY
		if (!(player.on_ground))
			gravity(&player.velocity.y);

		//	deal damage to player when hit by enemy projectile.
		for (int i = 0; i < MAX_TURRET_PROJECTILE; i++)
			if (deal_damage_to_player(&turret_projectiles[i], &boss_turrets[i], &player))
				iframe_cd = iframe_dur;

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	ENEMY AI
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	Update melee enemy state and behavior
		state_change(&melee_enemy[0], &platform[0], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy2 state and behaviour
		state_change(&melee_enemy[1], &platform[1], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy3 state and behaviour
		state_change(&melee_enemy[2], &platform[2], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy4 state and behaviour
		state_change(&melee_enemy[3], &platform[3], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy4 state and behaviour
		state_change(&melee_enemy[4], &platform[0], &player, 3.0f, 8.0f, &elapsedtime);

		//	BOSS shoot when player is on platform
		if (player.on_ground == 1 && (player.y >= platform[0].y - player.width * 2) && (player.y <= platform[0].y - player.width / 2)) {
			turret_projectiles[0].live = 1;
		}
		if (player.on_ground == 1 && (player.y >= platform[1].y - player.width * 2) && (player.y <= platform[1].y - player.width / 2)) {
			turret_projectiles[1].live = 1;
		}
		if (player.on_ground == 1 && (player.y >= platform[2].y - player.width * 2) && (player.y <= platform[2].y - player.width / 2)) {
			turret_projectiles[2].live = 1;
		}
		if (player.on_ground == 1 && (player.y >= platform[3].y - player.width * 2) && (player.y <= platform[3].y - player.width / 2)) {
			turret_projectiles[3].live = 1;
		}

		for (int i = 0; i < MAX_TURRET_PROJECTILE; i++) {
			if (turret_projectiles[i].live == 1) {
				enemy_shoot_projectile(&turret_projectiles[i], &boss_turrets[i], 1000);
			}
		}

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	KNOCKBACK COLLISION
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	collision between melee enemy and player
		if (iframe_cd == 0) {
			for (int i = 0; i < NUM_MAX_MELEE; i++) {
				if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy[i].x, melee_enemy[i].y, melee_enemy[i].width, melee_enemy[i].height)) {
					// Apply elastic collision
					ApplyElasticCollision(&player, melee_enemy[i], 1.f);
					player.on_ground = 0;
					player.HP -= 1;

					//	iframes
					iframe_cd = iframe_dur;
				}
			}
		}

		if (iframe_cd > 0.0f) {
			iframe_cd -= CP_System_GetDt();
			if (iframe_cd < 0.0f) {
				iframe_cd = 0;
			}
		}

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	HP of melee enemies and player
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	PLAYER DIES
		if (player.HP == 0) {
			is_dead = 1;
			pause_state(game_state);
			//	clear grapple
			drawGrapple(&player, &grapple.x, &grapple.y, platform, PLATFORM_SIZE, dt); 
		}
		//	BOSS DEFEATED
		update_boss_healthbar(&boss_health, boss1.health);
			// If boss is defeated
			if (boss1.health <= 0) {
				boss1.health = 0;  // Ensure health doesn't go negative
				update_boss_healthbar(&boss_health, 0);  // Update health bar one final time
				boss_dead = 1;	//	<----------ADD WIN SCREEN
				pause_state(game_state);
			}
		
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	GOAL INSTRUCTIONS
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	player reach goal point	-	print instructions.
	if (AreC_RIntersecting(player.x, player.y, 40, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawTextBox("Defeat the boss to win!", 50, 630, 100);
	}

	//	draw player
	CP_Settings_Fill(CP_Color_Create(250, 250, 250, 255));
	if (iframe_cd > 0)
		//	flashing player during iframe
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);

	//	draw boss
	draw_boss(&boss1);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawTextBox("Boss", 1500, 400, 100);

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	UI
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	PLAYER HEALTHBAR	(player_health_background);
	// Draw hearts
	draw_hearts(player_healthbar, player.HP);
	//	BOSS HEALTHBAR
	draw_healthbar(boss_health);
	draw_healthbar(boss_health_background);
	
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); // exit using Q
	}
	//	pause menu
	if (is_paused) {
		if (is_dead) {
			restart_menu(game_state, Levelboss_Init, Levelboss_Update, Levelboss_Exit);
		}
		else if (boss_dead) {
			level_clear("Assets/Save_File/level_4.txt");
			win_menu(game_state, Levelboss_Init, Levelboss_Update, Levelboss_Exit);
		}
		else {
			pause_menu(game_state, Levelboss_Init, Levelboss_Update, Levelboss_Exit);
		}
	}
	//	esc to pause game
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		pause_state(game_state);
	}
}

void Levelboss_Exit(void)
{
	// Free heart images
	for (int i = 0; i < MAX_HEALTH; ++i) {
		CP_Image_Free(&player_healthbar[i].heart);
	}

}