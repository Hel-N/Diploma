#pragma once

using namespace std;

struct Point {
	double x;
	double y;
};

struct Line
{
	Point a;
	Point b;
	double length;
};

double GetDistance(double x1, double y1, double x2, double y2);
double GetDistance(Point a, Point b);

double GetAngle(double x1, double y1, double x2, double y2);
double GetEquivPositiveAngle(double angle);

