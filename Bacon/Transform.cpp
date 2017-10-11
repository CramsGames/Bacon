#include "stdafx.h"
#include "Transform.h"
#include <glm/gtx/transform.hpp>

Transform::Transform (const glm::dvec3 &pos, const glm::dquat &rot, const glm::dvec3 &scale, const glm::dvec3 &origin) :
	position (pos), rotation (rot), scale (scale), origin (origin) {}

void Transform::Rotate (const glm::dvec3 &axis, double angle) {
	rotation *= glm::angleAxis (angle, axis);
}
void Transform::RotateAround (const glm::dvec3 &axis, double angle, glm::dvec3 &point) {
	glm::dvec3 b = (point - position);
	if (b != glm::dvec3 ()) {
		double twoBSquared = 2.0 * glm::length2 (b);
		position += glm::normalize (b * glm::angleAxis (glm::half_pi<double > () - angle * 0.5, axis)) * sqrt (twoBSquared - twoBSquared * cos (angle));
	}
	rotation *= glm::angleAxis (angle, axis);
}

glm::dmat4 Transform::LocalToWorldPointMatrixD () const {
	glm::dmat4 translationMatrix = glm::translate (position);
	glm::dmat4 orignMatrix = glm::translate (-origin);
	glm::dmat4 rotationMatrix = glm::mat4_cast (rotation);
	glm::dmat4 scaleMatrix = glm::scale (scale);
	return translationMatrix * rotationMatrix * orignMatrix * scaleMatrix;
}
glm::dmat4 Transform::WorldToLocalPointMatrixD () const {
	glm::dmat4 translationMatrix = glm::translate (-(position - origin));
	glm::dmat4 rotationMatrix = glm::mat4_cast (-rotation);
	glm::dmat4 scaleMatrix = glm::scale (-scale);
	return scaleMatrix * rotationMatrix * translationMatrix;
}

glm::mat4 Transform::LocalToWorldPointMatrixS () const {
	glm::mat4 translationMatrix = glm::translate (position);
	glm::mat4 orignMatrix = glm::translate (-origin);
	glm::mat4 rotationMatrix = glm::mat4_cast (rotation);
	glm::mat4 scaleMatrix = glm::scale (scale);
	return translationMatrix * rotationMatrix * orignMatrix * scaleMatrix;
}
glm::mat4 Transform::WorldToLocalPointMatrixS () const {
	glm::mat4 translationMatrix = glm::translate (-(position - origin));
	glm::mat4 rotationMatrix = glm::mat4_cast (-rotation);
	glm::mat4 scaleMatrix = glm::scale (-scale);
	return scaleMatrix * rotationMatrix * translationMatrix;
}

glm::dvec3 Transform::RightD () const {
	return rotation * glm::dvec4 (-1, 0, 0, 0);
}
glm::dvec3 Transform::LeftD () const {
	return rotation * glm::dvec4 (1, 0, 0, 0);
}
glm::dvec3 Transform::UpD () const {
	return rotation * glm::dvec4 (0, 1, 0, 0);
}
glm::dvec3 Transform::DownD () const {
	return rotation * glm::dvec4 (0, -1, 0, 0);
}
glm::dvec3 Transform::ForwardD () const {
	return rotation * glm::dvec4 (0, 0, 1, 0);
}
glm::dvec3 Transform::BackD () const {
	return rotation * glm::dvec4 (0, 0, -1, 0);
}

glm::vec3 Transform::RightS () const {
	return rotation * glm::dvec4 (-1, 0, 0, 0);
}
glm::vec3 Transform::LeftS () const {
	return rotation * glm::dvec4 (1, 0, 0, 0);
}
glm::vec3 Transform::UpS () const {
	return rotation * glm::dvec4 (0, 1, 0, 0);
}
glm::vec3 Transform::DownS () const {
	return rotation * glm::dvec4 (0, -1, 0, 0);
}
glm::vec3 Transform::ForwardS () const {
	return rotation * glm::dvec4 (0, 0, 1, 0);
}
glm::vec3 Transform::BackS () const {
	return rotation * glm::dvec4 (0, 0, -1, 0);
}

const glm::dvec3 &Transform::PositionD () const {
	return position;
}
const glm::dquat &Transform::RotationD () const {
	return rotation;
}
const glm::dvec3 &Transform::ScaleD () const {
	return scale;
}

const glm::vec3 Transform::PositionS () const {
	return glm::vec3 (position);
}
const glm::quat Transform::RotationS () const {
	return glm::quat (rotation);
}
const glm::vec3 Transform::ScaleS () const {
	return glm::vec3 (scale);
}