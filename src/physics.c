/*
 * physics.c
 *
 *  Created on: 27 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <time.h>
#include <stddef.h>

const long nanosPerTick = 10000000;
const long a;
const int maxUpdates = 5;
int missedUpdates = 0;
struct timespec lastUpdate = NULL;

void update(struct entity *es, int length) {
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	long delta = lastUpdate == NULL ?
	             nanosPerTick :
	             currentTime.tv_nsec + (currentTime.tv_sec - lastUpdate.tv_sec) * 1000000000
                 - lastUpdate.tv_sec;
	if (lastUpdate == NULL || delta >= nanosPerTick) {
		int iterations = delta / nanosPerTick + missedUpdates;
		if (iterations > maxUpdates) {
			missedUpdates += iterations - maxUpdates;
			iterations = maxUpdates;
		}

		for (int i = 0; i < length; i++) {
			es[i]->update(es[i]);
		}

		lastUpdate = clock_gettime(CLOCK_MONOTONIC, &currentTime);
	}
}
