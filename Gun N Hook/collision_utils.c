#include <math.h>
#include "cprocessing.h"

// rect-plane		probably don't need
int c_rect_line(float rect_x, float rect_y, float rect_width, float rect_height, float plane_x1, float plane_y1, float plane_x2, float plane_y2) {
	if (((plane_x1 <= (rect_x + rect_width / 2) && plane_x1 >= (rect_x - rect_width / 2)) && (plane_y1 <= (rect_y + rect_height / 2) && plane_y1 >= (rect_y - rect_height / 2))) ||
		((plane_x2 <= (rect_x + rect_width / 2) && plane_x2 >= (rect_x - rect_width / 2)) && (plane_y2 <= (rect_y + rect_height / 2) && plane_y2 >= (rect_y - rect_height / 2))))
		return 1;
	else
		return 0;
}

// rect-rect		player collide boss || player collide e_projectile || boss p_projectile		WORKS!!
int c_rect_rect(float rect1_x, float rect1_y, float rect1_width, float rect1_height, float rect2_x, float rect2_y, float rect2_width, float rect2_height) {
	if (abs(rect1_x - rect2_x) < (rect1_width / 2 + rect2_width / 2) && abs(rect1_y - rect2_y) < (rect1_height / 2 + rect2_height / 2))
		return 1;
	else
		return 0;
}

// point-rect || point-plane	grapple
int c_rect_point(float rect_x, float rect_y, float rect_width, float rect_height, float point_x, float point_y) {

	if ((point_x >= (rect_x - rect_width / 2)) && (point_x <= (rect_x + rect_width / 2)) &&
		(point_y >= (rect_y - rect_height / 2)) && (point_y <= (rect_y + rect_height / 2)))
		return 1;
	else
		return 0;
}
