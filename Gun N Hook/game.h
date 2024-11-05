#pragma once
typedef struct {
	float x, y;  // x and y components of the velocity
} Velocity;

// Define a struct for Player
typedef struct {
	float x, y;  // x and y coordinates of the player position
	int on_ground;
	Velocity velocity;  // Nested struct for velocity
	float diameter;
	float width,height;
} Player;

typedef struct {
	float x, y;  // x and y components of the velocity
	float on_wall;
} Grapple;

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);