#include "stdafx.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float time = 0;

// Clears the current window and draws a triangle.
void display() {
	
	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);
	GLint M = 32;
	GLint N = 32;
	GLint width = 1960;
	GLint height = 1960;
	GLfloat w = 2.0 / (float)(M + 0.50);
	GLfloat h = 2.0 / (float)(N - 0.75);
	GLfloat cx = (-1.0 + 0.5*w);	// x-coord for center of first triangle fan
	GLfloat cy = (-1.0 + 0.5*h);	// y-coord for center of first triangle fan
	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)width / (float)height;
	glOrtho(-aspect, aspect, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat v = (rand() % 100 + 1)/100.f;     // v in the range 1 to 100

	// outer loop is for traversing Y
	for (int j = 0; j < N; j++) {
		
		if (j == 1) cx = -1.0 + w;
		else if (j % 2 == 0) cx = -1.0 + 0.5 * w;
		else cx = cx = (-1.0 + w);
		// inner loop is for traversing X
		for (int i = 0; i < M; i++){
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(v, (1-v), 0);			glVertex2f(cx, cy);					// C
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx + 0.5*w, cy + 0.25*h);// 1
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx, cy + 0.5*h);			// 2
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx - 0.5*w, cy + 0.25*h);// 3
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx - 0.5*w, cy - 0.25*h);// 4
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx, cy - 0.5*h);			// 5
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx + 0.5*w, cy - 0.25*h);// 6
			glColor3f(1.0, 1.0, 1.0);	glVertex2f(cx + 0.5*w, cy + 0.25*h);// 7
			glEnd();
			cx += w;
			time += 0.1;
		}
		cy += 0.75*h;	
		time += 0.1;
	}
	
	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
	//time += 1.0;
	glutPostRedisplay();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {

	// Use a single buffered window in RGB mode (as opposed to a double-buffered
	// window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Position window at (80,80)-(480,380) and give it a title.
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(1960,1960);
	glutCreateWindow("Hex Grid");

	// Tell GLUT that whenever the main window needs to be repainted that it
	// should call the function display().
	glutDisplayFunc(display);

	// Tell GLUT to start reading and processing events.  This function
	// never returns; the program only exits when the user closes the main
	// window or kills the process.
	glutMainLoop();
}