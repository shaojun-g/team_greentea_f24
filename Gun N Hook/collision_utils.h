#pragma once

// rect-plane		player platforming (
int c_rect_line(float rect_center_x, float rect_center_y, float rect_width, float rect_height, float plane_x1, float plane_x2, float plane_y1, float plane_y2);
// rect-rect		player collide boss || player collide e_projectile || boss p_projectile
int c_rect_rect(float rect1_center_x, float rect1_center_y, float rect1_width, float rect1_height, float rect2_center_x, float rect2_center_y, float rect2_width, float rect2_height);
// point-rect		grapple
int c_rect_point(float rect_center_x, float rect_center_y, float rect_width, float rect_height, float point_x, float point_y);
