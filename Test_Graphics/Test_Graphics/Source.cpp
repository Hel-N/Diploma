#pragma comment(lib, "glut32.lib")
#define _USE_MATH_DEFINES
#include "glut.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int win_width = 640;
int win_height = 480;
int win_far = 10;

double l = 75;
double ll = 40;
double al = 0.0;
double x = 0.0, y = 0.0;
int steps = 10;

vector<pair<int, int>> points;
vector<vector<pair<int, double>>> g; // v, l
vector<int> supports; // точки опоры
int fl_fall = 0; // -1 - left, 0 - balance, 1 - right
double alpha = 0.0;
double d_alpha = 0.0;
int os;

double getAngle(int x1, int y1, int x2, int y2) {   //         / x2,y2
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

	res = atan(abs(1.0*y2 - y1) / abs(1.0*x2 - x1));
	if (x2 > x1 && y2 > y1)
		return res;
	if (x2 < x1 && y2 > y1)
		return res = M_PI - res;
	if (x2 < x1 && y2 < y1)
		return res = M_PI + res;
	if (x2 > x1 && y2 < y1)
		return res = 2 * M_PI - res;
}

double getDistance(int x1, int y1, int x2, int y2) {
	double res = sqrt(1.0*(x1 - x2)*(x1 - x2) + 1.0*(y1 - y2)*(y1 - y2));
	return res;
}

double getCenterOfGravity() {
	double sum_momets = 0.0;
	double sum_mass = 0.0;
	double res = 0.0;

	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			double cx = 1.0*(points[i].first + points[g[i][j].first].first) / 2; // координата x центра тяжести
			sum_mass += g[i][j].second; // g[i][j].second - длина отрезка, и т.к. 1 ед. длины = 1 ед. массы, то используем длину
			sum_momets += cx*g[i][j].second; // плечо на массу
		}
	}
	return res = sum_momets / sum_mass;
}

void Draw() {

	glBegin(GL_LINES);
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			glVertex2f(points[i].first, points[i].second);
			glVertex2f(points[g[i][j].first].first, points[g[i][j].first].second);
		}
	}
	glEnd();

	/*glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);
	glVertex2f(-win_width/2, -2 * ll);
	glVertex2f(win_width/2, -2 * ll);

	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, l);
	glVertex2f(l, l);
	glVertex2f(l, 0);
	glVertex2f(0, 0);
	glVertex2f(l, l);
	glVertex2f(0, l);
	glVertex2f(l, 0);
	glVertex2f(0, 0);

	//glVertex2f(-ll, -ll);
	//glVertex2f(0, -2*ll);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-ll, -ll);

	glVertex2f(-ll, -ll);
	glVertex2f(0, -2 * ll);

	glVertex2f(0, l);
	glVertex2f(l + ll, -ll);

	glVertex2f(l + ll, -ll);
	glVertex2f(l, -2 * ll);
	glEnd();*/

	/*glBegin(GL_LINES); // Начало отрисовки в указанном формате
	glVertex2f(0, 0);
	glVertex2f(x, y);
	glEnd(); // Закончили указывать вершины, которые будут отрисовываться
	*/
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT); // Очищает экран
	//Draw
	Draw();
	//

	glFlush(); // Выводит на экран буфер
	glutSwapBuffers(); // ???
}

void tick() // функция в которой будет все обновляться  
{
	if (fl_fall == -1) {
		if (steps != 1) { //изменить
			steps--;
			for (int i = 0; i < points.size(); ++i) {
				if (i == os) continue;
				double d = getDistance(points[os].first, points[os].second, points[i].first, points[i].second);
				double angle = getAngle(points[os].first, points[os].second, points[i].first, points[i].second) + d_alpha;
				points[i].first = d*cos(angle) + points[os].first;
				points[i].second = d*sin(angle) + points[os].second;
			}
		}
	}
	else if (fl_fall == 1) {
		if (steps != 0) { //изменить
			steps--;
			for (int i = 0; i < points.size(); ++i) {
				if (i == os) continue;
				double d = getDistance(points[os].first, points[os].second, points[i].first, points[i].second);
				double angle = getAngle(points[os].first, points[os].second, points[i].first, points[i].second) - d_alpha;
				points[i].first = d*cos(angle) + points[os].first;
				points[i].second = d*sin(angle) + points[os].second;
			}
		}
	}
}

void timer(int = 0) // Таймер игры(промежуток времени, в котором будет производится все процессы) 
{
	Display(); // Вызов функций   
	tick();
	glutTimerFunc(100, timer, 0); // новый вызов таймера( 100 - промежуток времени(в милисекундах), через который он будет вызыватся, timer - вызываемый паблик) 
}

int main(int argc, char** ardv) {
	// добавить проверку на наличие одинаковых координат
	points.push_back({ 50, 150 });
	points.push_back({ 100, 150 });
	points.push_back({ 100, 100 });
	points.push_back({ 50, 100 });
	points.push_back({ 0, 50 });
	points.push_back({ 50, 0 });
	points.push_back({ /*75*/ 53, 0 });

	g.resize(7);
	g[0].push_back({ 1, 50 });
	g[1].push_back({ 2, 50 });
	g[2].push_back({ 3, 50 });
	g[3].push_back({ 0, 50 });
	g[3].push_back({ 4, 50 * sqrt(2) });
	g[4].push_back({ 5, 50 * sqrt(2) });
	g[5].push_back({ 6, /*25*/ 3 });

	supports.push_back(5);
	supports.push_back(6);

	for (int i = 0; i < points.size(); ++i) {
		points[i].first += 100;
	}

	double cg = getCenterOfGravity();
	sort(supports.begin(), supports.end()); // обновляться!!!!!!!!!!!!!!!

	if (points[supports[0]].first > cg) {
		fl_fall = -1;
		os = supports[0];

		double alpha = 0.0;
		for (int i = 0; i < points.size(); ++i) {
			if (i == os) continue;
			double atmp = getAngle(points[os].first, points[os].second, points[i].first, points[i].second);
			if (atmp > alpha)
				alpha = M_PI - atmp;
		}
		//alpha = getAngle(points[os].first, points[os].second, points[2].first, points[2].second);
		d_alpha = alpha / steps;
	}
	else if (points[supports[supports.size() - 1]].first < cg)
	{
		fl_fall = 1;
		os = supports[supports.size() - 1];

		double alpha = 3 * M_PI;
		for (int i = 0; i < points.size(); ++i) {
			if (i == os) continue;
			double atmp = getAngle(points[os].first, points[os].second, points[i].first, points[i].second);
			if (atmp < alpha)
				alpha = atmp;
		}
		//alpha = getAngle(points[os].first, points[os].second, points[2].first, points[2].second);
		d_alpha = alpha / steps;
	}
	

	glutInit(&argc, ardv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Test_1");
	glClearColor(0, 0, 0, 1.0); // цвет очистки экрана RGBAlpha

	glMatrixMode(GL_PROJECTION);//????
	glLoadIdentity(); //????
	gluOrtho2D(0, win_width, 0, win_height); // Ортогональная система координат (3D декартова система координат)


	glutDisplayFunc(Display);
	glutTimerFunc(50, timer, 0);

	glutMainLoop(); // Запуск основного цикла OpenGL
	return 0;
}