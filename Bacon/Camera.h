#pragma once
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera (Transform *transform, glm::dmat4 projection);
	glm::dmat4 WorldToCameraMatrixD () const;
	glm::mat4 WorldToCameraMatrixS () const;
	glm::dmat4 ProjectionD () const;
	glm::mat4 ProjectionS () const;

	Transform *transform;
	glm::dmat4 projection;
};

