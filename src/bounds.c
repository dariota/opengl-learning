/*
 * bounds.c
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <stddef.h>
#include <stdlib.h>

#include "bounds.h"

struct boundingBox *newBoundingBox(float *positions[6], int length) {
	struct boundingBox *b = malloc(sizeof(struct boundingBox));

	b->length = length;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 6; j++) {
			b->positions[i][j] = positions[i][j];
		}
	}
	return b;
}

struct collision *interact(struct collision *c, struct boundingBox *a,
                          struct boundingBox *b) {
	return NULL;
}

struct boundingBox *copyOfBoundingBox(struct boundingBox *b) {
	struct boundingBox *copy = newBoundingBox(b->positions, b->length);
	return copy;
}

void freeBoundingBox(struct boundingBox *b) {
	if (!b) return;

	free(b->positions);
	free(b);
}
