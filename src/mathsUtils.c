/*
 * mathsUtils.c
 *
 *  Created on: 26 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include "mathsUtils.h"

void crossProduct(float *result, float *vec1, float *vec2) {
	result[VEC_X] = vec1[VEC_Y] * vec2[VEC_Z] - vec1[VEC_Z] * vec2[VEC_Y];
	result[VEC_Y] = vec1[VEC_Z] * vec2[VEC_X] - vec1[VEC_X] * vec2[VEC_Z];
	result[VEC_Z] = vec1[VEC_X] * vec2[VEC_Y] - vec1[VEC_Y] * vec2[VEC_X];

	normalise(result);
}

void normalise(float *vec) {
	normaliseLen(vec, 3);
}

void normaliseLen(float *vec, int len) {
	double max = vec[0];
	for (int i = 1; i < len; i++) {
		if (max < vec[i]) {
			max = vec[i];
		}
	}

	for (int i = 0; i < len; i++) {
		vec[i] /= max;
	}
}
