/*
 * camera.c
 *
 *  Created on: 25 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#include <stdlib.h>

#include "camera.h"
#include "mathsUtils.h"

struct camera *defaultCamera(void) {
	struct camera *myCamera = malloc(sizeof(struct camera));

	// angle of rotation for the camera direction
	myCamera->angleH = 0.0;
	myCamera->angleV = 0.0;

	// actual vector representing the camera's direction
	myCamera->look[VEC_X] = 0.0f;
	myCamera->look[VEC_Y] = 0.0f;
	myCamera->look[VEC_Z] = -1.0f;

	// XZ position of the camera
	myCamera->xyz[VEC_X] = 0.0f;
	myCamera->xyz[VEC_Y] = 0.75f;
	myCamera->xyz[VEC_Z] = 5.0f;

	return myCamera;
}

void freeCamera(struct camera *c) {
	free(c);
}
