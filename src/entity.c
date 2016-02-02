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
