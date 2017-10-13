#pragma once
#include <string>
#include <GL/glew.h>	

class Shader {
public:
	Shader (const std::string &fileName, unsigned char shaders = VERTEX_F | FRAGMENT_F);
	virtual ~Shader ();
	void Bind ();

	enum {
		VERTEX_F = 1u,
		GEOMETRY_F = 2u,
		FRAGMENT_F = 4u
	};

protected:
	enum {
		VERTEX_S,
		GEOMETRY_S,
		FRAGMENT_S,
		NUM_SHADERS
	};

	unsigned char shaders;
	GLuint _program;
	GLuint _shaders [NUM_SHADERS];
};