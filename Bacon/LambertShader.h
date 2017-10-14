#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class LambertShader : public Shader {
public:
	LambertShader (const std::string &fileName);
	void Prepare ();
	void Update (const Transform &transform, const Camera &camera, const glm::vec3 &ambient, const glm::vec4 &lightPosition, const glm::vec3 &lightColour);
private:
	enum attributes {
		POSITION_A,
		TEXCOORD_A,
		NORMAL_A,
		NUM_ATTRIBUTES
	};
	enum uniforms {
		TRANSFORM_U,
		PROJECTION_U,
		AMBIENT_U,
		LIGHTPOSITION_U,
		LIGHTCOLOUR_U,
		NUM_UNIFORMS
	};
	GLuint _uniforms [NUM_UNIFORMS];
};