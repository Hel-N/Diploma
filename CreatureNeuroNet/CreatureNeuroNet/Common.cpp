#pragma once
#define _USE_MATH_DEFINES
#include "Common.h"
#include <cmath>

using namespace std;

double GetDistance(int x1, int y1, int x2, int y2) {
	double res = sqrt(1.0*(x2 - x1)*(x2 - x1) + 1.0*(y2 - y1)*(y2 - y1));
	return res;
}
double GetDistance(Point a, Point b) {
	double res = sqrt(1.0*(a.x - b.x)*(a.x - b.x) + 1.0*(a.y - b.y)*(a.y - b.y));
	return res;
}

double GetAngle(int x1, int y1, int x2, int y2) {   //         / x2,y2
	double res = 0.0;								//        /
													// x1,y1 /______
	if (x1 == x2) {
		if (y1 == y2)
			return res;
		if (y2 > y1)
			return res = M_PI / 2;
		else
			return res = 3 * M_PI / 2;
	}

	if (y1 == y2) {
		if (x2 > x1)
			return res = 0;
		else
			return res = M_PI;
	}

	res = atan((1.0*abs(y2 - y1)) / (1.0*abs(x2 - x1)));
	if (x2 > x1 && y2 > y1)
		return res;
	if (x2 < x1 && y2 > y1)
		return res = M_PI - res;
	if (x2 < x1 && y2 < y1)
		return res = M_PI + res;
	if (x2 > x1 && y2 < y1)
		return res = 2 * M_PI - res;
}