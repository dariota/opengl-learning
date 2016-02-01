/*
 * entity.h
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "bounds.h"

struct drawInfo {
	// TODO sprites or something
};

struct entity {
	int needsUpdate;
	struct boundingBox *bBox;
	struct drawInfo *draw;
	void (*update)(struct entity*);
};

struct player {
	struct entity e;
	struct camera *c;
	int buttons[10];
};

struct drawInfo *newDrawInfo(void);
struct drawInfo *copyOfDrawInfo(struct drawInfo *d);
void freeDrawInfo(struct drawInfo *d);

struct entity *newEntity(struct boundingBox *b, struct drawInfo *d);
void update(struct entity *e);
void freeEntity(struct entity *e);

struct player *newPlayer(struct entity *e, struct camera *c);
void pushButton(struct player *p, int button);
void releaseButton(struct player *p, int button);
void updatePlayer(struct entity *e);
void freePlayer(struct player *p);

#endif
