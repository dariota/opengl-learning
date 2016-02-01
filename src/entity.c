/*
 * entity.c
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <GL/freeglut_std.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include "entity.h"
#include "bounds.h"
#include "camera.h"
#include "mathsutils.h"

const float moveUnit = 0.1f;

struct drawInfo *newDrawInfo(void) {
	return NULL;
}

struct drawInfo *copyOfDrawInfo(struct drawInfo *d) {
	struct drawInfo *copy = newDrawInfo();
	return copy;
}

void freeDrawInfo(struct drawInfo *d) {
	// it's funny because if you ask me what kind of rendering/world this is,
	// the next line is my answer
	free(d);
}


struct entity *newEntity(struct boundingBox *b, struct drawInfo *d) {
	struct entity *e = malloc(sizeof(struct entity));
	if (!e) return NULL;

	e->needsUpdate = 0;
	e->bBox = b;
	e->draw = d;

	return e;
}

void update(struct entity *e) {
	if (e->needsUpdate > 0) {
		--(e->needsUpdate);
		e->update(e);
	}
}

void freeEntity(struct entity *e) {
	if (!e) return;

	freeBoundingBox(e->bBox);
	freeDrawInfo(e->draw);
	free(e);
}


// makes a copy of the entity, does not take ownership
struct player *newPlayer(struct entity *e, struct camera *c) {
	struct player *p = malloc(sizeof(struct player));
	if (!p) return NULL;

	p->e.bBox = copyOfBoundingBox(e->bBox);
	p->e.draw = copyOfDrawInfo(e->draw);
	p->e.update = updatePlayer;

	p->c = c;

	for (int i = 0; i < 10; i++) {
		p->buttons[i] = 0;
	}

	return p;
}

// special keys should have their highest bit set
void pushButton(struct player *p, int button) {
	if (!p || !button) return;

	int i = -1;
	while (p->buttons[++i] != 0 && i < 10);

	p->buttons[i] = button;
}

// special keys should be made negative
void releaseButton(struct player *p, int button) {
	if (!p || !button) return;

	int i = -1;
	while (p->buttons[++i] != button && i < 10);
	if (i < 10)
		p->buttons[i] = 0;
	//intentional assignment, shift buttons down until you get a zero
	while (i + 1 < 10 && (p->buttons[i] = p->buttons[i + 1]))
		i++;
}

void updatePlayer(struct entity *e) {
	struct player *p = (void *) e;

	int i = -1;
	while (p->buttons[++i] != 0) {
		struct camera *c = p->c;
		if (p->buttons[i] < 0) {
			switch (-p->buttons[i]) {
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
		} else {
			float ortho[3];
			float up[] = {0.0, 1.0, 0.0};
			switch (p->buttons[i]) {
			case 'a':
				crossProduct(&ortho[0], c->look, up);
				c->xyz[VEC_X] -= ortho[VEC_X] * moveUnit;
				c->xyz[VEC_Y] -= ortho[VEC_Y] * moveUnit;
				c->xyz[VEC_Z] -= ortho[VEC_Z] * moveUnit;
				break;
			case 'e':
				crossProduct(&ortho[0], c->look, up);
				c->xyz[VEC_X] += ortho[VEC_X] * moveUnit;
				c->xyz[VEC_Y] += ortho[VEC_Y] * moveUnit;
				c->xyz[VEC_Z] += ortho[VEC_Z] * moveUnit;
				break;
			case ',':
				c->xyz[VEC_X] += c->look[VEC_X] * moveUnit;
				c->xyz[VEC_Y] += c->look[VEC_Y] * moveUnit;
				c->xyz[VEC_Z] += c->look[VEC_Z] * moveUnit;
				break;
			case 'o':
				c->xyz[VEC_X] -= c->look[VEC_X] * moveUnit;
				c->xyz[VEC_Y] -= c->look[VEC_Y] * moveUnit;
				c->xyz[VEC_Z] -= c->look[VEC_Z] * moveUnit;
				break;
			}
		}
	}
}

void freePlayer(struct player *p) {
	if (!p) return;

	freeBoundingBox(p->e.bBox);
	freeDrawInfo(p->e.draw);
	freeCamera(p->c);
	free(p);

}
