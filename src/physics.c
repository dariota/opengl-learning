/*
 * physics.c
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <Windows.h>
#include <stddef.h>
#include <stdio.h>

#include "entity.h"

LARGE_INTEGER ticksPerUpdate;
LARGE_INTEGER lastUpdate;
const int maxUpdates = 5;
int missedUpdates = 0;

void initPhysics(void) {
	QueryPerformanceFrequency(&ticksPerUpdate);
	ticksPerUpdate.QuadPart /= 100;
	lastUpdate.QuadPart = 0;
}

void updatePhysics(struct entity **es, int length) {
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	long long delta = lastUpdate.QuadPart == 0 ?
	             ticksPerUpdate.QuadPart :
				 (currentTime.QuadPart - lastUpdate.QuadPart);
	if (delta >= ticksPerUpdate.QuadPart) {
		int iterations = delta / ticksPerUpdate.QuadPart + missedUpdates;
		if (iterations > maxUpdates) {
			missedUpdates += iterations - maxUpdates;
			iterations = maxUpdates;
		}

		for (int i = 0; i < length; i++) {
			if (update(es[i])) {
				// TODO collision stuff
			}
		}

		lastUpdate.QuadPart = currentTime.QuadPart;
	}
}
