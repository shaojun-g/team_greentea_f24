#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "levelboss.h"
#include "structs.h"
#include "stdio.h"
#include "stdbool.h"
#include "leveltwo.h"
#include "collision_utils.h"
#include "movement.h"
#include "enemy.h"
#include "levelthree.h"
#include "utils.h"

#define PLATFORM_SIZE 9
Platform platform[PLATFORM_SIZE];
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
Player player;
Grapple grapple;
MELEE_Enemy melee_enemy, melee_enemy2, melee_enemy3, melee_enemy4;
//RANGE_Enemy range_enemy, range_enemy2, range_enemy3;
//Projectile enemy_projectile, enemy_projectile2, enemy_projectile3;
enum{MAX_RANGE_Enemy = 3};
RANGE_Enemy range_enemies[MAX_RANGE_Enemy];
Bullet enemy_projectiles[MAX_RANGE_Enemy];
float dt, elapsedtime;
int is_paused;
int* game_state;

void Levelthree_Init(void)
{
	CP_System_SetFrameRate(60.0f);		//	limit to 60fps

	CP_TEXT_ALIGN_HORIZONTAL h_text = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL v_text = CP_TEXT_ALIGN_V_MIDDLE;
	//size for text box
	CP_Settings_TextSize(25.00f);
	CP_Settings_TextAlignment(h_text, v_text);
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	/*platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform3.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform4.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_enemy1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_enemy2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_enemy3.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);*/
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform[0] = (Platform){ CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 15.00,CP_Color_Create(255, 128, 128, 255) };
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform[1] = (Platform){ 525.00 , 650.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[1].left_limit = platform[1].x - platform[1].width / 2;
	platform[1].right_limit = platform[1].x + platform[1].width / 2;
	//platform2 is second platform
	platform[2] = (Platform){ 1075.00 , 650.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[2].left_limit = platform[2].x - platform[2].width / 2;
	platform[2].right_limit = platform[2].x + platform[2].width / 2;
	//platform3 is third platform
	platform[3] = (Platform){ 800.00 , 500.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[3].left_limit = platform[3].x - platform[3].width / 2;
	platform[3].right_limit = platform[3].x + platform[3].width / 2;
	//platform4 is forth platform
	platform[4] = (Platform){ 1125.00 , 350.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[4].left_limit = platform[4].x - platform[4].width / 2;
	platform[4].right_limit = platform[4].x + platform[4].width / 2;
	//platform enemy1 is where enemy1 is standing
	//stationary enemy platforms have 50.00 as width and 15.00 as height
	platform[5] = (Platform){ 25.00 , 600.00, 50.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform enemy2 is where enemy2 is standing
	platform[6] = (Platform){ 1575.00 , 600.00, 50.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform enemy3 is where enemy3 is standing
	platform[7] = (Platform){ 1575.00 , 325.00, 50.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform[8] = (Platform){ 1475.00 , 200.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	//start goal will be where user spawns
	goal_start.x = 100.00;
	goal_start.y = 765.00;
	goal_start.width = 40.00;
	goal_start.height = 70.00;
	goal_start.corner_radius = 10;
	//end goal will be where user goes to next map
	goal_end.x = 1550.00;
	goal_end.y = 165.00;
	goal_end.width = 40.00;
	goal_end.height = 70.00;
	goal_end.corner_radius = 10;
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
	// Initialize melee enemy
	CP_Settings_RectMode(CP_POSITION_CENTER);
	melee_enemy.width = 40;
	melee_enemy.height = 40;
	melee_enemy.x = platform[1].x;
	melee_enemy.y = platform[1].y - platform[1].height / 2 - melee_enemy.height / 2; // Place enemy just above platform
	melee_enemy.state = PATROL; // Start in patrol state
	melee_enemy.dir = RIGHT;
	melee_enemy.speed = 100;
	melee_enemy.health = 5;
	// Initialize melee enemy 2
	melee_enemy2.width = 40;
	melee_enemy2.height = 40;
	melee_enemy2.x = platform[2].x;
	melee_enemy2.y = platform[2].y - platform[2].height / 2 - melee_enemy2.height / 2; // Place enemy just above platform
	melee_enemy2.state = PATROL; // Start in patrol state
	melee_enemy2.dir = RIGHT;
	melee_enemy2.speed = 100;
	melee_enemy2.health = 5;
	// Initialize melee enemy 3
	melee_enemy3.width = 40;
	melee_enemy3.height = 40;
	melee_enemy3.x = platform[3].x;
	melee_enemy3.y = platform[3].y - platform[3].height / 2 - melee_enemy3.height / 2; // Place enemy just above platform
	melee_enemy3.state = PATROL; // Start in patrol state
	melee_enemy3.dir = RIGHT;
	melee_enemy3.speed = 100;
	melee_enemy3.health = 5;
	// Initialize melee enemy 4
	melee_enemy4.width = 40;
	melee_enemy4.height = 40;
	melee_enemy4.x = platform[4].x;
	melee_enemy4.y = platform[4].y - platform[4].height / 2 - melee_enemy4.height / 2; // Place enemy just above platform
	melee_enemy4.state = PATROL; // Start in patrol state
	melee_enemy4.dir = RIGHT;
	melee_enemy4.speed = 100;
	melee_enemy4.health = 5;
	// Initialize range enemy 1
	range_enemies[0].width = platform[5].width;
	range_enemies[0].height = 40;
	range_enemies[0].x = platform[5].x;
	range_enemies[0].y = platform[5].y - platform[5].height / 2 - range_enemies[0].height / 2;;
	range_enemies[0].shoot_posX = range_enemies[0].x;
	range_enemies[0].shoot_posY = range_enemies[0].y;
	range_enemies[0].dir = RIGHT;
	//range projectile
	//enemy_projectiles[0].x = range_enemies[0].shoot_posX;
	//enemy_projectiles[0].y = range_enemies[0].shoot_posY;
	//enemy_projectiles[0].diameter = 25;
	//enemy_projectiles[0].live = 1;
	// Initialize range enemy 2
	range_enemies[1].width = platform[6].width;
	range_enemies[1].height = 40;
	range_enemies[1].x = platform[6].x;
	range_enemies[1].y = platform[6].y - platform[6].height / 2 - range_enemies[1].height / 2;;
	range_enemies[1].shoot_posX = range_enemies[1].x;
	range_enemies[1].shoot_posY = range_enemies[1].y;
	range_enemies[1].dir = LEFT;
	//range projectile
	//enemy_projectiles[1].x = range_enemies[1].shoot_posX;
	//enemy_projectiles[1].y = range_enemies[1].shoot_posY;
	//enemy_projectiles[1].diameter = 25;
	//enemy_projectiles[1].live = 1;
	// Initialize range enemy 3
	range_enemies[2].width = platform[7].width;
	range_enemies[2].height = 40;
	range_enemies[2].x = platform[7].x;
	range_enemies[2].y = platform[7].y - platform[7].height / 2 - range_enemies[2].height / 2;;
	range_enemies[2].shoot_posX = range_enemies[2].x;
	range_enemies[2].shoot_posY = range_enemies[2].y;
	range_enemies[2].dir = LEFT;
	//range projectile
	//enemy_projectiles[2].x = range_enemies[2].shoot_posX;
	//enemy_projectiles[2].y = range_enemies[2].shoot_posY;
	//enemy_projectiles[2].diameter = 25;
	//enemy_projectiles[2].live = 1;

	player = (Player){ 100, 785, 30, 30, 5, 1, {0, 0} };
	grapple = (Grapple){ 0, 0, 0 };
	elapsedtime = 0;

	//pea-shooter init
	pea_shooter_init(bullets, &player.x, &player.y);

	for (int i = 0; i < MAX_RANGE_Enemy; i++) {
		enemy_projectiles[i].x = range_enemies[i].shoot_posX;
		enemy_projectiles[i].y = range_enemies[i].shoot_posY;
		enemy_projectiles[i].diameter = 25;
		enemy_projectiles[i].live = 1;
	}

	for (int i = 0; i < MAX_RANGE_Enemy; i++) {
		printf("enemy projectile x :%f\n", enemy_projectiles[i].x);
		printf("enemy projectile y :%f\n", enemy_projectiles[i].y);
		printf("enemy projectile diameter : %f\n", enemy_projectiles[i].diameter);
		printf("enemy projectile live : %d\n\n\n", enemy_projectiles[i].live);
	}
	for (int i = 0; i < MAX_RANGE_Enemy; i++) {
		printf("range_enemies  x :%f\n", range_enemies[i].x);
		printf("range_enemies  y :%f\n", range_enemies[i].y);
		printf("range_enemies  width :%f\n", range_enemies[i].width);
		printf("range_enemies  height :%f\n", range_enemies[i].height);
		printf("range_enemies  shoot_posX : %f\n", range_enemies[i].shoot_posX);
		printf("range_enemies  shoot_posY : %f\n\n\n", range_enemies[i].shoot_posY);
	}
	printf("player hp : %d\n\n\n", player.HP);
	
	//pause variables
	is_paused = 0;
	game_state = &is_paused;

}

void Levelthree_Update(void)
{
	dt = CP_System_GetDt();												//	date time function
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));	//	clear background to gray

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	DRAW
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	
	//	Draw melee enemy
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // Red color
	CP_Graphics_DrawRect(melee_enemy.x, melee_enemy.y, melee_enemy.width, melee_enemy.height);
	//	Draw melee enemy2
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
	CP_Graphics_DrawRect(melee_enemy2.x, melee_enemy2.y, melee_enemy2.width, melee_enemy2.height);
	//	Draw melee enemy3
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
	CP_Graphics_DrawRect(melee_enemy3.x, melee_enemy3.y, melee_enemy3.width, melee_enemy3.height);
	//	Draw melee enemy4
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
	CP_Graphics_DrawRect(melee_enemy4.x, melee_enemy4.y, melee_enemy4.width, melee_enemy4.height);

	//	draw range enemy projectiles
	for (int i = 0; i < MAX_RANGE_Enemy; i++) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawCircle(enemy_projectiles[i].x, enemy_projectiles[i].y, enemy_projectiles[i].diameter);
	}
	//	draw range enemy
	for (int i = 0; i < MAX_RANGE_Enemy; i++) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(range_enemies[i].x, range_enemies[i].y, range_enemies[i].width, range_enemies[i].height);
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

		//	deal damage to melee enemies
		deal_damage(bullets, &melee_enemy.x, &melee_enemy.y, &melee_enemy.width, &melee_enemy.height, &melee_enemy.health);
		deal_damage(bullets, &melee_enemy2.x, &melee_enemy2.y, &melee_enemy2.width, &melee_enemy2.height, &melee_enemy2.health);
		deal_damage(bullets, &melee_enemy3.x, &melee_enemy3.y, &melee_enemy3.width, &melee_enemy3.height, &melee_enemy3.health);
		deal_damage(bullets, &melee_enemy4.x, &melee_enemy4.y, &melee_enemy4.width, &melee_enemy4.height, &melee_enemy4.health);

		//	player basic movement		-	WASD and jump
		basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground);//start basic movement
		//	When player not on ground	-	GRAVITY
		if (!(player.on_ground))
			gravity(&player.velocity.y);
		
		//	deal damage to player when hit by enemy projectile.
		deal_damage_to_player(&enemy_projectiles[0], &range_enemies[0], &player);
		deal_damage_to_player(&enemy_projectiles[1], &range_enemies[1], &player);
		deal_damage_to_player(&enemy_projectiles[2], &range_enemies[2], &player);


		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	ENEMY AI
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	Update melee enemy state and behavior
		state_change(&melee_enemy, &platform[1], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy2 state and behaviour
		state_change(&melee_enemy2, &platform[2], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy3 state and behaviour
		state_change(&melee_enemy3, &platform[3], &player, 3.0f, 8.0f, &elapsedtime);
		//	update melee enemy4 state and behaviour
		state_change(&melee_enemy4, &platform[4], &player, 3.0f, 8.0f, &elapsedtime);

		// ranged enemy shoot projectile
		enemy_shoot_projectile(&enemy_projectiles[0], &range_enemies[0], 200);
		enemy_shoot_projectile(&enemy_projectiles[1], &range_enemies[1], 200);
		enemy_shoot_projectile(&enemy_projectiles[2], &range_enemies[2], 200);

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	KNOCKBACK COLLISION
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	collision between melee enemy and player
		if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy.x, melee_enemy.y, melee_enemy.width, melee_enemy.height)) {
			// Apply elastic collision
			ApplyElasticCollision(&player, melee_enemy, 1.f);
			player.HP -= 1;
			collisionCooldown = collisionCooldownDuration;	// Set cooldown timer
			player.on_ground = 0;
			printf("player hp : %i", player.HP);
		}
		if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy2.x, melee_enemy2.y, melee_enemy2.width, melee_enemy2.height)) {
			// Apply elastic collision
			ApplyElasticCollision(&player, melee_enemy2, 1.f);
			player.on_ground = 0;
			player.HP -= 1;
			collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		}
		if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy3.x, melee_enemy3.y, melee_enemy3.width, melee_enemy3.height)) {
			// Apply elastic collision
			ApplyElasticCollision(&player, melee_enemy3, 1.f);
			player.on_ground = 0;
			player.HP -= 1;
			collisionCooldown = collisionCooldownDuration;  // Set cooldown timer

		}
		if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy4.x, melee_enemy4.y, melee_enemy4.width, melee_enemy4.height)) {
			// Apply elastic collision
			ApplyElasticCollision(&player, melee_enemy4, 1.f);
			player.on_ground = 0;
			player.HP -= 1;
			collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		}


		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	HP of melee enemies and player
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	PLAYER DIES
		if (player.HP == 0) {
			//	clear grapple
			drawGrapple(&player, &grapple.x, &grapple.y, platform, PLATFORM_SIZE, dt); //draw grapple

			CP_Engine_SetNextGameStateForced(Levelthree_Init, Levelthree_Update, Levelthree_Exit);
			printf("next state updated");
		}
		//	ENEMY DIES
		if (melee_enemy.health <= 0) {
			melee_enemy.x = -1000; // A position far off the screen
			melee_enemy.y = -1000; // A position far off the screen
		}
		if (melee_enemy2.health <= 0) {
			melee_enemy2.x = -1000; // A position far off the screen
			melee_enemy2.y = -1000; // A position far off the screen
		}
		if (melee_enemy3.health <= 0) {
			melee_enemy3.x = -1000; // A position far off the screen
			melee_enemy3.y = -1000; // A position far off the screen
		}
		if (melee_enemy4.health <= 0) {
			melee_enemy4.x = -1000; // A position far off the screen
			melee_enemy4.y = -1000; // A position far off the screen
		}

		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	GOAL INSTRUCTIONS
		//-----------------------------------------------------------------------------------------------------------------------------------------//
		//	player reach goal point	-	print instructions.
		if (AreC_RIntersecting(player.x, player.y, 40, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
			//printf("touching start");
			CP_Font_DrawTextBox("Get to the Goal!", 50, 675, 100);
		}
		if (AreC_RIntersecting(player.x, player.y, 40, goal_end.x, goal_end.y, goal_end.width, goal_end.height)) {
			printf("intersect good");
			CP_Font_DrawTextBox("Press N to head to next level!", 1500, 200, 100);
			if (CP_Input_KeyTriggered(KEY_N))
			{
				CP_Engine_SetNextGameState(Levelboss_Init, Levelboss_Update, Levelboss_Exit); // next level using N
			}
		}
	}
	
	//	draw player
	CP_Settings_Fill(CP_Color_Create(250, 250, 250, 255));
	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	UI
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	//	draw_healthbar(player_health_background);
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);
	//	pause menu
	if (is_paused) {
		pause_menu(game_state, Levelthree_Init, Levelthree_Update, Levelthree_Exit);
	}
	//	esc to pause game
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		pause_state(game_state);
	}
}

void Levelthree_Exit(void)
{

}