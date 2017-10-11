#pragma once
#include "Camera.h"

class PerspCamera : public Camera {
public:
	PerspCamera (Transform *transform, int width, int height, double fov, double zNear, double zFar);
};

