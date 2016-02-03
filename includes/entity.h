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
	void (*draw)(void);
};

struct entity {
	int needsUpdate;
	struct boundingBox *bBox;
	struct drawInfo *draw;
	int (*update)(struct entity*);
	float xyz[3];
};

struct drawInfo *newDrawInfo(void (*draw)(void));
struct drawInfo *copyOfDrawInfo(struct drawInfo *d);
void freeDrawInfo(struct drawInfo *d);

struct entity *newEntity(struct boundingBox *b, struct drawInfo *d,
                         int (*update)(struct entity*), float x, float y, float z);
int update(struct entity *e);
void freeEntity(struct entity *e);

#endif
