#include <gl/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

double r = 50;
double scr_w = 600;
double scr_h = 400;

double point[10][2];	// 10 points with x,y
int num_of_p = 10;

int ran_x() {
	int x;
	x = rand() % (int)(scr_w - 2 * r) + (r + 1);
	return x;
}

int ran_y() {
	int y;
	y = rand() % (int)(scr_h - 2 * r) + (r + 1);
	return y;
}

int ran_gray() {
	int g;
	g = rand() % 2;	// 0: black->white	1: white->black (from top to bottom) 
	return g;
}

bool check_p(int p_num) {
	if (p_num == 0) // No need to check the first point
		return true;
	else
		for (int i = 0; i < p_num; i++) {
			double dis = sqrt((point[p_num][1] - point[i][1])*(point[p_num][1] - point[i][1]) + 
				(point[p_num][0] - point[i][0])*(point[p_num][0] - point[i][0]));
			if (dis < 2 * r)
				return false;
		}
	return true;
}

void generator_P() {
	srand(time(NULL));
	for (int i = 0; i < num_of_p; i++) {
		point[i][0] = ran_x();
		point[i][1] = ran_y();
		bool keep_check = true;
		while (keep_check) {
			if (check_p(i))
				keep_check = false;
			else {
				point[i][0] = ran_x();
				point[i][1] = ran_y();
			}
		}
	}
}


void drawL(void) {
	double t, p = 3.14159 / 180;
	double g = 1.0 / 180.0;
	int gray;
	glBegin(GL_LINES);
	generator_P();

	// Printing every disk
	for (int i = 0; i < num_of_p; i++) {
		// Randoming the gray pattern
		gray = ran_gray();
		if(gray == 0)	// Black to White
			for (int j = 90; j < 270; j++) {
				t = j * p;
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f((j - 90)*g, (j - 90)*g, (j - 90)*g);
				glVertex2f(point[i][0] + r * cos(t), point[i][1] + r * sin(t));
				glVertex2f(point[i][0] - r * cos(t), point[i][1] + r * sin(t));
			}
		else // White to Black
			for (int j = 90; j < 270; j++) {
				t = j * p;
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f((270 - j)*g, (270 - j)*g, (270 - j)*g);
				glVertex2f(point[i][0] + r * cos(t), point[i][1] + r * sin(t));
				glVertex2f(point[i][0] - r * cos(t), point[i][1] + r * sin(t));
			}
	}
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(scr_w, scr_h);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Project_1");
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, scr_w, 0.0, scr_h);
	glutDisplayFunc(drawL);
	glutMainLoop();
}