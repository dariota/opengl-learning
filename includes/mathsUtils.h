/*
 * mathsUtils.h
 *
 *  Created on: 26 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef MATHSUTILS_H
#define MATHSUTILS_H

#define VEC_X 0
#define VEC_Y 1
#define VEC_Z 2

#define PI 3.141592653f

// Assumes 3D vectors
void crossProduct(float *result, float *vec1, float *vec2);
void normalise(float *vec);
void normaliseLen(float *vec, int len);

#endif
