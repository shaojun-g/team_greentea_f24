#include "stdio.h"
#include "stdbool.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "leveltwo.h"
#include "levelone.h"
#include "collision_utils.h"
#include "movement.h"
#include "enemy.h"
#include "levelthree.h"


#define PLATFORM_SIZE 5
Platform platform_base, platform1, platform2, platform3, platform_goal;
Platform platform[PLATFORM_SIZE];
Player player;
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;
MELEE_Enemy melee_enemy, melee_enemy2, melee_enemy3;
RANGE_Enemy range_enemy;
Projectile enemy_projectile;


float dt;

void Leveltwo_Init(void)
{
	CP_Settings_TextSize(25.00f);
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform[0] = (Platform){ CP_System_GetWindowWidth() / 2 , 800.00, CP_System_GetWindowWidth(), 15.00,CP_Color_Create(255, 128, 128, 255) };
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform[1] = (Platform){ 700.00 , 650.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255)};
	platform[1].left_limit = platform[1].x - platform[1].width/2;
	platform[1].right_limit = platform[1].x + platform[1].width / 2;
	//platform2 is second platform
	platform[2] = (Platform){ 900.00 , 500.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[2].left_limit = platform[2].x - platform[2].width / 2;
	platform[2].right_limit = platform[2].x + platform[2].width / 2;
	//platform3 is third platform
	platform[3] = (Platform){ 1100.00 , 350.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
	platform[3].left_limit = platform[3].x - platform[3].width / 2;
	platform[3].right_limit = platform[3].x + platform[3].width / 2;
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform[4] = (Platform){ 1475.00 , 200.00, 250.00, 15.00, CP_Color_Create(255, 128, 128, 255) };
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
	
	//player values
	player = (Player){ 100, 785, 30, 30, 5, 1, {0, 0} };

	
	
}


void Leveltwo_Update(void)
{
	dt = CP_System_GetDt();//date time function
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	// Decrease cooldown time
	if (collisionCooldown > 0.0f) {
		collisionCooldown -= dt;
	}
	
	//draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	//draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);

		if (c_rect_rect(player.x, player.y, player.width, player.height, platform[i].x, platform[i].y, platform[i].width, platform[i].height)) {
			player.velocity.y = 0;
			player.on_ground = 1;
		}
	}
	// Draw melee enemy
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // Red color
	CP_Graphics_DrawRect(melee_enemy.x, melee_enemy.y, melee_enemy.width, melee_enemy.height);

	// Draw melee enemy2
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
	CP_Graphics_DrawRect(melee_enemy2.x, melee_enemy2.y, melee_enemy2.width, melee_enemy2.height);


	// Draw melee enemy3
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
	CP_Graphics_DrawRect(melee_enemy3.x, melee_enemy3.y, melee_enemy3.width, melee_enemy3.height);

	CP_Graphics_DrawRect(player.x, player.y, player.width, player.height);//draw player

	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground, dt);//start basic movement 

	if (player.on_ground != 1) {
		gravity(&player.y, &player.velocity.y, dt);
	}

	//draw healthbar (with background)
	//draw_healthbar(player_health_background);
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);

	// Update melee enemy state and behavior
	state_change(&melee_enemy, &platform[1], &player, 3.0f, 8.0f, 0);

	//update melee enemy2 state and behaviour
	state_change(&melee_enemy2, &platform[2], &player, 3.0f, 8.0f, 0);

	//update melee enemy2 state and behaviour
	state_change(&melee_enemy3, &platform[3], &player, 3.0f, 8.0f, 0);

	//collision between melee enemy and player
	if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy.x, melee_enemy.y, melee_enemy.width, melee_enemy.height)) {
		// Apply elastic collision
		
		ApplyElasticCollision(&player, melee_enemy, 1.f);
		player.on_ground = 0;
		player.HP -= 1;
		collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		printf("player hp : %i", player.HP);
		if (player.HP == 0) {
			player.HP = 5;
			CP_Engine_SetNextGameStateForced(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit);
			printf("next state updated");
		}
		
	}

	if(c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy2.x, melee_enemy2.y, melee_enemy2.width, melee_enemy2.height)) {
		// Apply elastic collision
		ApplyElasticCollision(&player, melee_enemy2, 1.f);
		player.on_ground = 0;
		player.HP -= 1;
		collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		if (player.HP == 0) {
			player.HP = 5;
			CP_Engine_SetNextGameStateForced(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit);
			printf("next state updated");
		}
		
	}

	if (c_rect_rect(player.x, player.y, player.width, player.height, melee_enemy3.x, melee_enemy3.y, melee_enemy3.width, melee_enemy3.height)) {
		// Apply elastic collision
		ApplyElasticCollision(&player, melee_enemy3, 1.f);
		player.on_ground = 0;
		player.HP -= 1;
		collisionCooldown = collisionCooldownDuration;  // Set cooldown timer
		if (player.HP == 0) {
			player.HP = 5;
			CP_Engine_SetNextGameStateForced(Leveltwo_Init, Leveltwo_Update, Leveltwo_Exit);
			printf("next state updated");
		}
		
	}


	if (AreCircles_GoalIntersecting(player.x, player.y, 40, goal_start.x, goal_start.y, goal_start.width, goal_start.height)) {
		
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255)); // Blue color
		CP_Font_DrawTextBox("Get to the Goal!", 50, 675, 100);
	}
	
	if (AreCircles_GoalIntersecting(player.x, player.y, 40, goal_end.x, goal_end.y, goal_end.width, goal_end.height)) {
		printf("intersect good");
		CP_Font_DrawTextBox("Press N to head to next level!", 1500, 200, 100);
		if (CP_Input_KeyTriggered(KEY_N))
		{
			CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit); // next level using N
		}
	}


}


void Leveltwo_Exit(void)
{

}