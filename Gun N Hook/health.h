#pragma once

typedef struct Healthbar {
	float rectx;
	float recty;
	float width;
	float height;
	CP_Color color;
} healthbar;

typedef struct Health {
	CP_Image heart;
	float x;
	float y;
	float width;
	float height;
} heart;

void draw_healthbar(healthbar health);

void draw_hearts(heart health[], int *size);

void remove_hearts(int* size);

void add_hearts(int* size);