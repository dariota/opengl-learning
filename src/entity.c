/*
 * entity.c
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <stdlib.h>
#include <stddef.h>

#include "entity.h"
#include "bounds.h"

struct drawInfo *newDrawInfo(void) {
	return NULL;
}
void freeDrawInfo(struct drawInfo *d) {
	// it's funny because if you ask me what kind of rendering/world this is,
	// the next line is my answer
	free(d);
}


struct entity *newEntity(struct boundingBox *b, struct drawInfo *d) {
	struct entity *e = malloc(sizeof(struct entity));
	if (!e) return NULL;

	e->bBox = b;
	e->draw = d;

	return e;
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

	p->c = c;

	for (int i = 0; i < 10; i++) {
		p->buttons[i] = 0;
	}

	return p;
}

void pushButton(struct player *p, int button) {
	if (!p || !button) return;

	int i = -1;
	while (p->buttons[++i] != 0);

	p->buttons[i] = button;
}

void releaseButton(struct player *p, int button) {
	if (!p || !button) return;

	int i = -1;
	while (p->buttons[++i] != button);
	p->buttons[i] = 0;
	//intentional assignment, shift buttons down until you get a zero
	while ((i + 1 < 10) && (p->buttons[i] = p->buttons[i + 1]));
}

void update(struct player *p, int iterations) {
	;
}

void freePlayer(struct player *p) {
	;
}
