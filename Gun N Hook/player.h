#pragma once

typedef struct {
	double x, y;  // x and y components of the velocity
} Velocity;

typedef struct {
	double x, y;  // x and y coordinates of the player position
	int on_ground;
	Velocity velocity;  // Nested struct for velocity
} Player;

void basic_movement(double* player_x, double* player_y, double* speed_x, double* speed_y, int* on_ground, double dt);

void gravity(double* player_y, double* speed_y, double dt);
