/*
 * bounds.h
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef BOUNDS_H
#define BOUNDS_H

#define VEC_H 3
#define VEC_V 4
#define VEC_D 5

struct boundingBox {
	// xyz of top left + height, width, depth for all cuboids forming the object
	int length;
	float *positions[6];
};

struct collision {
	float impulses[3];
	int impulseEnd;
	float instants[3];
	int instantEnd;
};

struct boundingBox *newBoundingBox(float *positions[6], int length);
struct collision *interact(struct collision *c, struct boundingBox *a,
                          struct boundingBox *b);
struct boundingBox *copyOfBoundingBox(struct boundingBox *b);
void freeBoundingBox(struct boundingBox *b);

#endif
