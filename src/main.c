/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees
 and is provided without guarantee or warrantee expressed or
 implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
 will write the equivalent Direct3D immediate mode program. */

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

#include "camera.h"
#include "mathsUtils.h"

//TODO: fixed step physics, delta time graphics?
// perform n physics updates, up to a cap, forces a slowdown to catch up if
// there's lag

//Alternatively: Event based update model per object, more useful for sims

struct camera *c;
float colour = 1.0f;
float up[] = {0, 1, 0};

void drawSnowMan() {
	glColor3f(colour, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glTranslatef(0.05f, 0.10f, 0.18f);
		glutSolidSphere(0.05f,10,10);
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(c->xyz[VEC_X], c->xyz[VEC_Y], c->xyz[VEC_Z],
	          c->xyz[VEC_X] + c->look[VEC_X],
			  c->xyz[VEC_Y] + c->look[VEC_Y],
			  c->xyz[VEC_Z] + c->look[VEC_Z],
			  up[VEC_X], up[VEC_Y], up[VEC_Z]);

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			glPushMatrix();
			glTranslatef(i * 10 - 30, 0, j * 10 - 30);
			drawSnowMan();
			glPopMatrix();
		}
	}

	glutSwapBuffers();

	glutPostRedisplay();
}

void changeSize(int width, int height) {
	if (height == 0)
		height = 1;
	float ratio = (1.0 * width) / height;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) {
	float fraction = 0.2f;
	float ortho[3];

	if (key == 'a' || key == 'e') {
		crossProduct(&ortho[0], c->look, up);
	}

	switch (key) {
		case 'a':
			c->xyz[VEC_X] -= ortho[VEC_X] * fraction;
			c->xyz[VEC_Y] -= ortho[VEC_Y] * fraction;
			c->xyz[VEC_Z] -= ortho[VEC_Z] * fraction;
			break;
		case 'e':
			c->xyz[VEC_X] += ortho[VEC_X] * fraction;
			c->xyz[VEC_Y] += ortho[VEC_Y] * fraction;
			c->xyz[VEC_Z] += ortho[VEC_Z] * fraction;
			break;
		case ',':
			c->xyz[VEC_X] += c->look[VEC_X] * fraction;
			c->xyz[VEC_Y] += c->look[VEC_Y] * fraction;
			c->xyz[VEC_Z] += c->look[VEC_Z] * fraction;
			break;
		case 'o':
			c->xyz[VEC_X] -= c->look[VEC_X] * fraction;
			c->xyz[VEC_Y] -= c->look[VEC_Y] * fraction;
			c->xyz[VEC_Z] -= c->look[VEC_Z] * fraction;
			break;
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			c->angleH -= 0.01f;
			c->look[VEC_X] = sin(c->angleH);
			c->look[VEC_Z] = -cos(c->angleH);
			break;
		case GLUT_KEY_RIGHT:
			c->angleH += 0.01f;
			c->look[VEC_X] = sin(c->angleH);
			c->look[VEC_Z] = -cos(c->angleH);
			break;
		case GLUT_KEY_UP:
			; // an empty statement is required  after a label as a declaration
			  // is not a statement
			float maxAngle = PI * (80.0/180);
			c->angleV = c->angleV >= maxAngle ? maxAngle : c->angleV + 0.01;
			c->look[VEC_Y] = sin(c->angleV);
			break;
		case GLUT_KEY_DOWN:
			;
			float minAngle = PI * (-80.0/180);
			c->angleV = c->angleV <= minAngle ? minAngle : c->angleV - 0.01;
			c->look[VEC_Y] = sin(c->angleV);
			break;
	}
}

int main(int argc, char **argv) {
	c = defaultCamera();

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Butts");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	free(c);

	return 0; /* ANSI C requires main to return int. */
}
