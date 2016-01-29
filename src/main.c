#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

#include "camera.h"
#include "mathsUtils.h"
#include "entity.h"
#include "physics.h"

// Alternatively: Event based update model per object, more useful for sims

struct player *p;
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

void processKeys(unsigned char key, int x, int y) {
	pushButton(p, key);
}

void releaseKeys(unsigned char key, int x, int y) {
	releaseButton(p, key);
}

void processSpecialKeys(int key, int x, int y) {
	pushButton(p, -key);
}

void releaseSpecialKey(int key, int x, int y) {
	releaseButton(p, -key);
}

int main(int argc, char **argv) {
	fprintf(stderr, "hi main");
	struct entity *e = newEntity(newBoundingBox(NULL, 0), newDrawInfo());
	fprintf(stderr, "entity made");
	p = newPlayer(e, defaultCamera());
	fprintf(stderr, "player made");
	p->c = c = defaultCamera();

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Butts");
	fprintf(stderr, "glut done");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(releaseKeys);
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(releaseSpecialKey);
	fprintf(stderr, "keys done");

	glEnable(GL_DEPTH_TEST);
	initPhysics();

	glutMainLoop();

	freePlayer(p);

	return 0;
}
