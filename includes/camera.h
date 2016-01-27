/*
 * camera.h
 *
 *  Created on: 25 Jan 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef CAMERA_H
#define CAMERA_H

struct camera {
	// angle of rotation for the camera direction
	float angleH, angleV;

	// actual vector representing the camera's direction
	float look[3];

	// XZ position of the camera
	float xyz[3];
};

struct camera *defaultCamera(void);

#endif
