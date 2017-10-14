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

Mesh::Mesh (Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices) {
	_drawCount = numIndices;

	std::vector<glm::vec3> positions = std::vector <glm::vec3> (numVertices);
	std::vector<glm::vec2> texcoords = std::vector <glm::vec2> (numVertices);
	std::vector<glm::vec3> normals = std::vector <glm::vec3> (numVertices);

	for (int i = 0; i < numVertices; i++) {
		positions.push_back (vertices [i].position);
		texcoords.push_back (vertices [i].texcoord);
		normals.push_back (vertices [i].normal);
	}

	glGenVertexArrays (1, &_vertexArrayObject);
	glBindVertexArray (_vertexArrayObject);

	glGenBuffers (NUM_BUFFERS, _vertexArrayBuffers);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [POSITION_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].position), &positions [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [TEXCOORD_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].texcoord), &texcoords [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [NORMAL_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].normal), &normals [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (2);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers [INDEX_VB]);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof (indices [0]), indices, GL_STATIC_DRAW);

	glBindVertexArray (0);

	positions.clear ();
	texcoords.clear ();
	normals.clear ();
}

Mesh::Mesh (std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	int numVertices = static_cast<unsigned int> (vertices.size ());
	int numIndices = static_cast<unsigned int> (indices.size ());
	_drawCount = numIndices;

	std::vector<glm::vec3> positions = std::vector <glm::vec3> ();
	std::vector<glm::vec2> texcoords = std::vector <glm::vec2> ();
	std::vector<glm::vec3> normals = std::vector <glm::vec3> ();

	positions.reserve (numVertices);
	texcoords.reserve (numVertices);
	normals.reserve (numVertices);

	for (int i = 0; i < numVertices; i++) {
		positions.push_back (vertices [i].position);
		texcoords.push_back (vertices [i].texcoord);
		normals.push_back (vertices [i].normal);
	}

	glGenVertexArrays (1, &_vertexArrayObject);
	glBindVertexArray (_vertexArrayObject);

	glGenBuffers (NUM_BUFFERS, _vertexArrayBuffers);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [POSITION_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].position), &positions [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [TEXCOORD_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].texcoord), &texcoords [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ARRAY_BUFFER, _vertexArrayBuffers [NORMAL_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices [0].normal), &normals [0], GL_STATIC_DRAW);
	glEnableVertexAttribArray (2);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers [INDEX_VB]);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof (indices [0]), &indices [0], GL_STATIC_DRAW);

	glBindVertexArray (0);

	positions.clear ();
	texcoords.clear ();
	normals.clear ();
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