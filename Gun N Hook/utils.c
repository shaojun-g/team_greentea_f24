#include <math.h>
#include <stdio.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	//Calculate the half width and height of rectangle
	double HW = area_width / 2;
	double HH = area_height / 2;

	//Determine the boundary of the rectangle
	double left = area_center_x - HW;
	double right = area_center_x + HW;
	double top = area_center_y - HH;
	double bottom = area_center_y + HH;

	if (click_x >= left && click_x <= right && click_y >= top && click_y <= bottom) {
		return 1;
	}
	else {
		return 0;
	};
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	//Calculate the radius
	double radius = diameter / 2;

	//Calculate the distance between the click point and the circle's center
	double distance_squared = CP_Math_Square(click_x - circle_center_x) + CP_Math_Square(click_y - circle_center_y);

	if (distance_squared < CP_Math_Square(radius)) {
		return 1;
	}
	else {
		return 0;
	};
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	double distance = CP_Math_Distance(c2_x, c2_y, c1_x, c1_y);

	/*return ((distance <= (r1 + r2)) && (distance >= fabs(r1 - r2)) );*/
	if (distance < (r1 + r2)) {
		return 1;
	}
	else {
		return 0;
	}
}