#include "stdafx.h"
#include "GBuffer.h"

#include <iostream>


GBuffer::GBuffer (unsigned int windowWidth, unsigned int windowHeight) {
	// Create the FBO
	glGenFramebuffers (1, &_fbo);
	glBindFramebuffer (GL_DRAW_FRAMEBUFFER, _fbo);

	// Create the gbuffer textures
	glGenTextures (GBUFFER_NUM_TEXTURES, _textures);
	glGenTextures (1, &_depthTexture);

	for (unsigned int i = 0; i < GBUFFER_NUM_TEXTURES; i++) {
		glBindTexture (GL_TEXTURE_2D, _textures [i]);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _textures [i], 0);
	}

	// depth
	glBindTexture (GL_TEXTURE_2D, _depthTexture);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

	GLenum DrawBuffers [] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
	glDrawBuffers (4, DrawBuffers);

	GLenum Status = glCheckFramebufferStatus (GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "FB error, status: 0x%x\n" << Status << std::endl;
		return;
	}

	// restore default FBO
	glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);
}


GBuffer::~GBuffer () {
	glDeleteFramebuffers (1, &_fbo);
}

void GBuffer::BindForWriting () {
	glBindFramebuffer (GL_DRAW_FRAMEBUFFER, _fbo);
}

void GBuffer::BindForReading () {
	glBindFramebuffer (GL_READ_FRAMEBUFFER, _fbo);
}