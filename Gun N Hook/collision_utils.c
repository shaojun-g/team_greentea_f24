#include <math.h>
#include "cprocessing.h"

// rect-line	-	DIVIDES LINE IN 5 POINTS: THEN RECT-POINT FOR EACH.
int c_rect_line(float rect_x, float rect_y, float rect_width, float rect_height, float line_x1, float line_y1, float line_x2, float line_y2) {
	//	define rect edges
	float rectleft	= rect_x - rect_width	/ 2;
	float rectright	= rect_x + rect_width	/ 2;
	float recttop	= rect_y - rect_height	/ 2;
	float rectbot	= rect_y + rect_height	/ 2;

	//	divide into many points: X
	float linexQUART	= (line_x1 + line_x2) / 2;
	float linexHALF		= (line_x1 + linexQUART) / 2;
	float linex3QUART	=	(line_x2 + linexQUART) / 2;
	//	divide into many points: Y
	float lineyQUART = (line_y1 + line_y2) / 2;
	float lineyHALF = (line_y1 + lineyQUART) / 2;
	float liney3QUART = (line_y2 + lineyQUART) / 2;
	//	arrays for loop.
	float lineArrX[5] = { line_x1, linexQUART, linexHALF, linex3QUART, line_x2 };
	float lineArrY[5] = { line_y1, lineyQUART, lineyHALF, liney3QUART, line_y2 };

	for (int i = 0; i < 5; ++i) {
		if ((lineArrX[i] >= rectleft) && (lineArrX[i] <= rectright) &&
			(lineArrY[i] >= recttop) && (lineArrY[i] <= rectbot))
			return 1;
	}

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
