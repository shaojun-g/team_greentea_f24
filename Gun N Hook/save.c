/* file:	save.c
// author:	Muhamad Amzar Bin Mohamad Zamre
// email:	muhamadamzar.b@digipen.edu
// work done: Definition of file_check, level_progress,
// level_clear and level_reset
//
//
// brief:	This file contains the implementation for
// save.c
//
//
// Copyright @ 2020 DigiPen, All rights reserved.
//--------------------------------------------------------- */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cprocessing.h"
#include "utils.h"



bool file_check(const char *level) {
	FILE *check = fopen( level, "r");
	
	if (!check) {
		perror("file does not exist/cannot be accessed");

		return false;
	}
	
	if (check) {
		fclose(check);
		return true;
	}
	return false;
}

int level_progress(const char* level) {
	FILE* check = fopen(level, "r");
	if (!check) {
		// Handle error if file cannot be opened
		fprintf(stderr, "file could not be opened");
		exit(EXIT_FAILURE);
		return 0;
	}

	int num;
	fscanf_s(check, "%d", &num);
	if (num == 1) {
		return 1;
	}
	fclose(check);
	return 0;
}



void level_clear(char const *goal) {
	FILE *open = fopen(goal, "w");
	
	if (!open) {
		perror("file does not exist/cannot be accessed");
		exit(EXIT_FAILURE);
	}

	fprintf(open, "%d", 1);
	fclose(open);

}

void level_reset(char const* check) {
	FILE *open = fopen(check, "w");

	if (!open) {
		perror("file does not exist/cannot be accessed");
		exit(EXIT_FAILURE);
	}

	fprintf(open, "%d", 0);
	fclose(open);

	
}

