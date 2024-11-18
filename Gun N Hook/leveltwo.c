#include "stdio.h"
#include "mainmenu.h"
#include "cprocessing.h"
#include "utils.h"
#include "levelthree.h"
#include "collisionlib.h"

Platform platform_base, platform1, platform2, platform3, platform_goal;
Goal goal_start, goal_end;
Healthbar player_health, player_health_background;

void Leveltwo_Init(void)
{
	//game window size is (1600, 900)
	//set all platform color as the same(dark red)
	platform_base.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform1.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform2.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform3.platform_color = CP_Color_Create(255, 128, 128, 255);
	platform_goal.platform_color = CP_Color_Create(255, 128, 128, 255);
	//set healthbar color 
	player_health.rect_color = CP_Color_Create(255, 0, 0, 255);
	player_health_background.rect_color = CP_Color_Create(255, 0, 0, 100);
	//platform_base is the ground 
	platform_base.x = CP_System_GetWindowWidth() / 2;
	platform_base.y = 800.00;
	platform_base.width = CP_System_GetWindowWidth();
	platform_base.height = 10.00;
	//platform1 is first platform
	//all platforms increment at y coordinates by 150.00f
	//all platforms increment at x coordinates by minimum 200.00f
	//default platforms will have 150.00f as width and 15.00f as height
	platform1.x = 600.00;
	platform1.y = 650.00;
	platform1.width = 250.00;
	platform1.height = 15.00;
	//platform2 is second platform
	platform2.x = 800.00;
	platform2.y = 500.00;
	platform2.width = 250.00;
	platform2.height = 15.00;
	//platform3 is third platform
	platform3.x = 1000.00;
	platform3.y = 350.00;
	platform3.width = 250.00;
	platform3.height = 15.00;
	//platform goal will be where user gets to head to next level
	//default platform goal width will be 250.00f
	platform_goal.x = 1475.00;
	platform_goal.y = 200.00;
	platform_goal.width = 250.00;
	platform_goal.height = 15.00;
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
}


void Leveltwo_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255)); // clear background to gray
	//draw goals
	draw_goal(goal_start);
	draw_goal(goal_end);
	//draw all platforms
	for (int i = 0; i < PLATFORM_SIZE; i++) {
		draw_platform(platform[i]);

		collide_platform(&player, &platform[i]);
	}

	basic_movement(&player.x, &player.y, &player.velocity.x, &player.velocity.y, &player.on_ground);//start basic movement
	if (!(player.on_ground))
		gravity(&player.velocity.y);

	//pea shooter function
	pea_shooter(bullets, &player.x, &player.y);

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

	//if (player.on_ground != 1) {
	//	gravity(&player.y, &player.velocity.y, dt);
	//}

	//draw healthbar (with background)
	//draw_healthbar(player_health_background);
	draw_healthbar(player_health_background);
	draw_healthbar(player_health);


	// Update melee enemy state and behavior
	state_change(&melee_enemy, &platform[1], &player, 3.0f, 8.0f, &elapsedtime);

	//update melee enemy2 state and behaviour
	state_change(&melee_enemy2, &platform[2], &player, 3.0f, 8.0f, &elapsedtime);

	//update melee enemy2 state and behaviour
	state_change(&melee_enemy3, &platform[3], &player, 3.0f, 8.0f, &elapsedtime);


	
	//damage for melee enemy
	deal_damage(bullets, &melee_enemy.x, &melee_enemy.y, &melee_enemy.width, &melee_enemy.height, &melee_enemy.health);

	deal_damage(bullets, &melee_enemy2.x, &melee_enemy2.y, &melee_enemy2.width, &melee_enemy2.height, &melee_enemy2.health);

	deal_damage(bullets, &melee_enemy3.x, &melee_enemy3.y, &melee_enemy3.width, &melee_enemy3.height, &melee_enemy3.health);

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
	//test for next level (this will be for goal function)
	if (CP_Input_KeyTriggered(KEY_N))
	{
		CP_Engine_SetNextGameState(Levelthree_Init, Levelthree_Update, Levelthree_Exit); // next level using N
	}

}

void Leveltwo_Exit(void)
{

}