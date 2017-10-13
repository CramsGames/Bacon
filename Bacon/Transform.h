#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
	glm::dvec3 position;
	glm::dquat rotation;
	glm::dvec3 scale;
	glm::dvec3 origin;

	Transform (const glm::dvec3 &pos = glm::dvec3 (), const glm::dquat &rot = glm::dquat (), const glm::dvec3 &scale = glm::dvec3 (1.0, 1.0, 1.0), const glm::dvec3 &origin = glm::dvec3 (0.0, 0.0, 0.0));

	void Rotate (const glm::dvec3 &axis, double angle);
	void RotateAround (const glm::dvec3 &axis, double angle, glm::dvec3 &point);

	glm::dmat4 LocalToWorldPointMatrixD () const;
	glm::dmat4 WorldToLocalPointMatrixD () const;

	glm::mat4 LocalToWorldPointMatrixS () const;
	glm::mat4 WorldToLocalPointMatrixS () const;

	glm::dvec3 RightD () const;
	glm::dvec3 LeftD () const;
	glm::dvec3 UpD () const;
	glm::dvec3 DownD () const;
	glm::dvec3 ForwardD () const;
	glm::dvec3 BackD () const;

	glm::vec3 RightS () const;
	glm::vec3 LeftS () const;
	glm::vec3 UpS () const;
	glm::vec3 DownS () const;
	glm::vec3 ForwardS () const;
	glm::vec3 BackS () const;

	const glm::dvec3 &PositionD () const;
	const glm::dquat &RotationD () const;
	const glm::dvec3 &ScaleD () const;

	const glm::vec3 PositionS () const;
	const glm::quat RotationS () const;
	const glm::vec3 ScaleS () const;
};