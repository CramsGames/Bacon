#include "stdafx.h"
#include "Camera.h"

Camera::Camera (Transform *transform, glm::dmat4 projection)
	: transform (transform), projection (projection) {}

glm::dmat4 Camera::ProjectionD () const {
	return projection;
}
glm::mat4 Camera::ProjectionS () const {
	return projection;
}

glm::dmat4 Camera::WorldToCameraMatrixD () const {
	return ProjectionD () * glm::lookAt (transform->PositionD (), transform->PositionD () + transform->ForwardD (), transform->UpD ());
}
glm::mat4 Camera::WorldToCameraMatrixS () const {
	return ProjectionS () * glm::lookAt (transform->PositionS (), transform->PositionS () + transform->ForwardS (), transform->UpS ());
}