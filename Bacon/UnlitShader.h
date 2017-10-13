#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class UnlitShader : public Shader {
public:
	UnlitShader (const std::string &fileName);
	void Prepare ();
	void Update (const Transform &transform, const Camera &camera);
private:
	enum attributes {
		POSITION_A,
		TEXCOORD_A,
		NUM_ATTRIBUTES
	};
	enum uniforms {
		TRANSFORM_U,
		NUM_UNIFORMS
	};
	GLuint _uniforms [NUM_UNIFORMS];
};