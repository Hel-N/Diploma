#pragma once

using namespace std;

struct Point {
	int x;
	int y;
};

struct Line
{
	Point a;
	Point b;
	double length;
};

double GetDistance(int x1, int y1, int x2, int y2);
double GetDistance(Point a, Point b);

double GetAngle(int x1, int y1, int x2, int y2);
