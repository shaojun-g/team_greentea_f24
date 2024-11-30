// file:	collisionlib.h
// author:	Chewn Thing Kwan
// email:	Kwan.c@digipen.edu
// co-author: Benjamin Ban
// email:	k.ban@digipen.edu
// 
// brief: declarations of intersection functions to be used for
// collision functions in collisionlib.c.
// 
// Copyright @ 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

// rect-plane		player platforming (prob remove)
int c_rect_line(float rect_x, float rect_y, float rect_width, float rect_height, float line_x1, float line_y1, float* line_x2, float* line_y2);
// rect-rect		player collide boss || player collide e_projectile || boss p_projectile
int c_rect_rect(float rect1_center_x, float rect1_center_y, float rect1_width, float rect1_height, float rect2_center_x, float rect2_center_y, float rect2_width, float rect2_height);
// point-rect		grapple
int c_rect_point(float rect_center_x, float rect_center_y, float rect_width, float rect_height, float point_x, float point_y);