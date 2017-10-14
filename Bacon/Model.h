#pragma once

#include "Vertex.h"
#include "Mesh.h"
#include <vector>

class Model {
public:
	Model (std::vector<Vertex> &vertices = std::vector<Vertex> (), std::vector<unsigned int> &indices = std::vector<unsigned int> ());
	Model (Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
	~Model ();

	Mesh ToMesh ();

	static Model Quad (float xMin = 0.0f, float xMax = 1.0f, float yMin = 0.0f, float yMax = 1.0f);
	static Model Cube24 (float xMin = 0.0f, float xMax = 1.0f, float yMax = 0.0f, float yMin = 1.0f);

	static Model Load (const std::string& fileName);

private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
};