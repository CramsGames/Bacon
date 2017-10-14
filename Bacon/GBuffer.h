#pragma once

#include <gl\glew.h>

class GBuffer {
public:
	GBuffer (unsigned int windowWidth, unsigned int windowHeight);
	~GBuffer ();

	void BindForWriting ();
	void BindForReading ();

	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

private:
	GLuint _fbo;
	GLuint _textures [GBUFFER_NUM_TEXTURES];
	GLuint _depthTexture;
};