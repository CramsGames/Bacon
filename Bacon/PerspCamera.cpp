#include "stdafx.h"
#include "PerspCamera.h"

PerspCamera::PerspCamera (Transform *transform, int width, int height, double fov, double zNear, double zFar)
	: Camera (transform, glm::perspective (fov, double (width) / double (height), zNear, zFar)) {}