#include <math.h>
#include <stdio.h>
#include "cprocessing.h"
#include "health.h"
#include "utils.h"



void draw_healthbar(healthbar health) {
	CP_Settings_Fill(health.color);
	CP_Graphics_DrawRect(health.rectx, health.recty, health.width, health.height);
}


void draw_hearts(heart heart[],int *size) {
	float spacing = 50.f;
	for (int i = 0; i < *size; ++i) {
		float gap = spacing * i;
		CP_Image_Draw(heart[i].heart, heart[i].x + gap, heart[i].y, heart[i].width, heart[i].height, 255);
	}
}

void remove_hearts(int* size) {
	*size -= 1;
}

void add_hearts(int* size) {
	*size += 1;
}