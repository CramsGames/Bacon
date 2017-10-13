#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh (glm::vec3 *vertexPositions, glm::vec2 *vertexTexCoords, glm::vec3 *vertexNormals, unsigned int numVertices, unsigned int* indices, unsigned int numIndices) {
	_drawCount = numIndices;

	glGenVertexArrays (1, &_vertexArrayObject);
	glBindVertexArray (_vertexArrayObject);

	glGenBuffers (NUM_BUFFERS, _vertexArrayBuffers);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [POSITION_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertexPositions [0]), vertexPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [TEXCOORD_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertexTexCoords [0]), vertexTexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [NORMAL_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertexNormals [0]), vertexNormals, GL_STATIC_DRAW);
	glEnableVertexAttribArray (2);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers [INDEX_VB]);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof (indices [0]), indices, GL_STATIC_DRAW);

	glBindVertexArray (0);
}

Mesh::~Mesh () {
	glDeleteBuffers (NUM_BUFFERS, _vertexArrayBuffers);
	glDeleteVertexArrays (1, &_vertexArrayObject);
}

void Mesh::Draw () {
	glBindVertexArray (_vertexArrayObject);
	glDrawElements (GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray (0);
}