#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

class Mesh {
public:
	Mesh (glm::vec3 *vertexPositions, glm::vec2 *vertexTexCoords, glm::vec3 *vertexNormals, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	~Mesh ();

	void Draw ();

	inline size_t VertexCount () {
		return _drawCount;
	}

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

private:
	unsigned int _drawCount;
	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers [NUM_BUFFERS];
};

