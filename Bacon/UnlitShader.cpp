#include "stdafx.h"
#include "UnlitShader.h"

UnlitShader::UnlitShader (const std::string &fileName) : Shader (fileName) {
	glBindAttribLocation (_program, POSITION_A, "position");
	glBindAttribLocation (_program, TEXCOORD_A, "texCoord");

	_uniforms [TRANSFORM_U] = glGetUniformLocation (_program, "transform");
}

void UnlitShader::Prepare () {
	glEnable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);
}

void UnlitShader::Update (const Transform &transform, const Camera &camera) {
	glm::mat4 matrix = camera.WorldToCameraMatrixS () * transform.LocalToWorldPointMatrixS ();
	glUniformMatrix4fv (_uniforms [TRANSFORM_U], 1, GL_FALSE, &matrix [0] [0]);
}