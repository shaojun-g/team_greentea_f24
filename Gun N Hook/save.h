/* file:	save.c
// author:	Muhamad Amzar Bin Mohamad Zamre
// email:	muhamadamzar.b@digipen.edu
// work done: Definition of file_check, level_progress,
// level_clear and level_reset
//
//
// brief:	This file contains the declaration for
// file_check, level_progress, level_clear and level_reset
//
//
// Copyright @ 2020 DigiPen, All rights reserved.
//--------------------------------------------------------- */
#pragma once

int file_check(char const *level);

int level_progress(char const* level);

void level_clear(char const* goal);

void level_reset(char const* check);

