#pragma once
#include <string>
#include <GL/glew.h>

class Texture {
public:
	Texture (std::string fileName);
	virtual ~Texture ();

	int Width ();
	int Height ();

	void Bind (unsigned int unit);
private:
	int _width, _height;
	GLuint _texture;
};

