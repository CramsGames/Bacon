#include "stdafx.h"
#include "LambertShader.h"

LambertShader::LambertShader (const std::string &fileName) : Shader (fileName) {
	glBindAttribLocation (_program, POSITION_A, "position");
	glBindAttribLocation (_program, TEXCOORD_A, "texCoord");
	glBindAttribLocation (_program, NORMAL_A, "normal");

	_uniforms [TRANSFORM_U] = glGetUniformLocation (_program, "transform");
	_uniforms [PROJECTION_U] = glGetUniformLocation (_program, "projection");
	_uniforms [AMBIENT_U] = glGetUniformLocation (_program, "ambient");
	_uniforms [LIGHTPOSITION_U] = glGetUniformLocation (_program, "lightPosition");
	_uniforms [LIGHTCOLOUR_U] = glGetUniformLocation (_program, "lightColour");
}

void LambertShader::Prepare () {
	glEnable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);
}

void LambertShader::Update (const Transform &transform, const Camera &camera, const glm::vec3 &ambient, const glm::vec4 &lightPosition, const glm::vec3 &lightColour) {
	glUniformMatrix4fv (_uniforms [TRANSFORM_U], 1, GL_FALSE, &transform.LocalToWorldPointMatrixS () [0] [0]);
	glUniformMatrix4fv (_uniforms [PROJECTION_U], 1, GL_FALSE, &camera.WorldToCameraMatrixS () [0] [0]);
	glUniform3fv (_uniforms [AMBIENT_U], 1, &ambient [0]);
	glUniform4fv (_uniforms [LIGHTPOSITION_U], 1, &lightPosition [0]); //&(glm::vec4 (lightPosition) * transform.WorldToLocalMatrixFloat ())[0]
	glUniform3fv (_uniforms [LIGHTCOLOUR_U], 1, &(lightColour / transform.ScaleS ()) [0]);
}