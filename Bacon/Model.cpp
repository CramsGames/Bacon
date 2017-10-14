#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tobj\tiny_obj_loader.h"

Model::Model (std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
	: _vertices (vertices), _indices (indices) {
	if (_indices.size () == 0) {
		unsigned int numIndices = static_cast<unsigned int> (vertices.size ());
		_indices.reserve (numIndices);
		for (unsigned int i = 0; i < numIndices; i++)
			_indices.push_back (i);
	}
}

Model::Model (Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount) {
	_vertices = std::vector <Vertex> ();
	_indices = std::vector <unsigned int> ();
	_vertices.reserve (vertexCount);
	_indices.reserve (indexCount);

	for (unsigned int i = 0; i < vertexCount; i++)
		_vertices.push_back (vertices [i]);
	for (unsigned int i = 0; i < indexCount; i++)
		_indices.push_back (indices [i]);

	if (indexCount == 0) {
		_indices.reserve (vertexCount);
		for (unsigned int i = 0; i < vertexCount; i++)
			_indices.push_back (i);
	}
}

Model::~Model () {
	_vertices.clear ();
	_indices.clear ();
}

Mesh Model::ToMesh () {
	return Mesh (_vertices, _indices);
}

Model Model::Quad (float xMin, float xMax, float yMin, float yMax) {
	Vertex vertices [] {
		Vertex (glm::vec3 (-0.5f, -0.5f, 0), glm::vec2 (xMin, yMin), glm::vec3 (0, 0, -1)),
		Vertex (glm::vec3 (0.5f, -0.5f, 0), glm::vec2 (xMax, yMin), glm::vec3 (0, 0, -1)),
		Vertex (glm::vec3 (-0.5f, 0.5f, 0), glm::vec2 (xMin, yMax), glm::vec3 (0, 0, -1)),
		Vertex (glm::vec3 (0.5f, 0.5f, 0), glm::vec2 (xMax, yMax), glm::vec3 (0, 0, -1))
	};
	unsigned int indices [] = {2, 1, 0, 3, 1, 2};
	return Model (&vertices [0], 4, &indices [0], 6);
}
Model Model::Cube24 (float xMin, float xMax, float yMax, float yMin) {
	Vertex vertices [] {
		Vertex (glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec2 (xMin, yMax), glm::vec3 (0.0f, 0.0f, -1.0f)),
		Vertex (glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec2 (xMax, yMax), glm::vec3 (0.0f, 0.0f, -1.0f)),
		Vertex (glm::vec3 (-0.5f, 0.5f, -0.5f), glm::vec2 (xMin, yMin), glm::vec3 (0.0f, 0.0f, -1.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, -0.5f), glm::vec2 (xMax, yMin), glm::vec3 (0.0f, 0.0f, -1.0f)),

		Vertex (glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec2 (xMin, yMax), glm::vec3 (1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, -0.5f, 0.5f), glm::vec2 (xMax, yMax), glm::vec3 (1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, -0.5f), glm::vec2 (xMin, yMin), glm::vec3 (1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, 0.5f), glm::vec2 (xMax, yMin), glm::vec3 (1.0f, 0.0f, 0.0f)),

		Vertex (glm::vec3 (0.5f, -0.5f, 0.5f), glm::vec2 (xMin, yMax), glm::vec3 (0.0f, 0.0f, 1.0f)),
		Vertex (glm::vec3 (-0.5f, -0.5f, 0.5f), glm::vec2 (xMax, yMax), glm::vec3 (0.0f, 0.0f, 1.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, 0.5f), glm::vec2 (xMin, yMin), glm::vec3 (0.0f, 0.0f, 1.0f)),
		Vertex (glm::vec3 (-0.5f, 0.5f, 0.5f), glm::vec2 (xMax, yMin), glm::vec3 (0.0f, 0.0f, 1.0f)),

		Vertex (glm::vec3 (-0.5f, -0.5f, 0.5f), glm::vec2 (xMin, yMax), glm::vec3 (-1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec2 (xMax, yMax), glm::vec3 (-1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (-0.5f, 0.5f, 0.5f), glm::vec2 (xMin, yMin), glm::vec3 (-1.0f, 0.0f, 0.0f)),
		Vertex (glm::vec3 (-0.5f, 0.5f, -0.5f), glm::vec2 (xMax, yMin), glm::vec3 (-1.0f, 0.0f, 0.0f)),

		Vertex (glm::vec3 (-0.5f, 0.5f, -0.5f), glm::vec2 (xMin, yMax), glm::vec3 (0.0f, 1.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, -0.5f), glm::vec2 (xMax, yMax), glm::vec3 (0.0f, 1.0f, 0.0f)),
		Vertex (glm::vec3 (-0.5f, 0.5f, 0.5f), glm::vec2 (xMin, yMin), glm::vec3 (0.0f, 1.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, 0.5f, 0.5f), glm::vec2 (xMax, yMin), glm::vec3 (0.0f, 1.0f, 0.0f)),

		Vertex (glm::vec3 (-0.5f, -0.5f, 0.5f), glm::vec2 (xMin, yMax), glm::vec3 (0.0f, -1.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, -0.5f, 0.5f), glm::vec2 (xMax, yMax), glm::vec3 (0.0f, -1.0f, 0.0f)),
		Vertex (glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec2 (xMin, yMin), glm::vec3 (0.0f, -1.0f, 0.0f)),
		Vertex (glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec2 (xMax, yMin), glm::vec3 (0.0f, -1.0f, 0.0f))
	};
	unsigned int indices [] = {
		2, 1, 0, 3, 1, 2,
		6, 5, 4, 7, 5, 6,
		10, 9, 8, 11, 9, 10,
		14, 13, 12, 15, 13, 14,
		18, 17, 16, 19, 17, 18,
		22, 21, 20, 23, 21, 22
	};
	return Model (&vertices [0], 24, &indices [0], 36);
}

void split (const std::string &s, char delim, std::vector<std::string>& result) {
	std::stringstream ss;
	ss.str (s);
	std::string item;
	for (int i = 0; std::getline (ss, item, delim); i++) {
		result [i] = item;
	}
}

Model Model::Load (const std::string& fileName) {

	std::vector<Vertex> vertices = std::vector<Vertex> ();
	std::vector<unsigned int> indices = std::vector<unsigned int> ();

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj (&attrib, &shapes, &materials, &err, fileName.c_str ())) {
		throw std::runtime_error (err);
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex;

			if (index.texcoord_index != -1) {
				if (index.normal_index != -1) {
					vertex = Vertex ({
						attrib.vertices [3 * index.vertex_index + 0],
						attrib.vertices [3 * index.vertex_index + 1],
						attrib.vertices [3 * index.vertex_index + 2]
					}, {
						attrib.texcoords [2 * index.texcoord_index + 0],
						1.0f - attrib.texcoords [2 * index.texcoord_index + 1]
					}, {
						attrib.normals [3 * index.normal_index + 0],
						attrib.normals [3 * index.normal_index + 1],
						attrib.normals [3 * index.normal_index + 2]
					});
				} else {
					vertex = Vertex ({
						attrib.vertices [3 * index.vertex_index + 0],
						attrib.vertices [3 * index.vertex_index + 1],
						attrib.vertices [3 * index.vertex_index + 2]
					}, {
						attrib.texcoords [2 * index.texcoord_index + 0],
						1.0f - attrib.texcoords [2 * index.texcoord_index + 1]
					});
				}
			} else {
				if (index.normal_index != -1) {
					vertex = Vertex ({
						attrib.vertices [3 * index.vertex_index + 0],
						attrib.vertices [3 * index.vertex_index + 1],
						attrib.vertices [3 * index.vertex_index + 2]
					}, {
						0,
						0
					}, {
						attrib.normals [3 * index.normal_index + 0],
						attrib.normals [3 * index.normal_index + 1],
						attrib.normals [3 * index.normal_index + 2]
					});
				} else {
					vertex = Vertex ({
						attrib.vertices [3 * index.vertex_index + 0],
						attrib.vertices [3 * index.vertex_index + 1],
						attrib.vertices [3 * index.vertex_index + 2]
					});
				}
			}

			vertices.push_back (vertex);
			indices.push_back (static_cast<unsigned int> (indices.size ()));
		}
	}

	return Model (vertices, indices);


	/*
	std::ifstream objectFile;
	objectFile.open (fileName);

	if (!objectFile) {
		std::cerr << "Failed to open file: " << fileName.c_str () << std::endl;
		return Model ();
	}

	std::string data;
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexTexCoords;
	std::vector<glm::vec3> vertexNormals;
	std::vector<Vertex> vertices;
	//std::vector<unsigned int> positionIndices;
	//std::vector<unsigned int> texCoordIndices;
	//std::vector<unsigned int> normalIndices;

	while (!objectFile.eof ()) {
		std::getline (objectFile, data);
		std::stringstream ss (data);
		std::string type;
		ss >> type;
		std::vector<std::string> sd = std::vector<std::string> (3);
		if (type == "v") {
			ss >> sd [0] >> sd [1] >> sd [2];
			vertexPositions.push_back (glm::vec3 (atof (sd [0].c_str ()), atof (sd [1].c_str ()), atof (sd [2].c_str ())));
		} else if (type == "vn") {
			ss >> sd [0] >> sd [1] >> sd [2];
			vertexNormals.push_back (glm::vec3 (atof (sd [0].c_str ()), atof (sd [1].c_str ()), atof (sd [2].c_str ())));
		} else if (type == "vt") {
			ss >> sd [0] >> sd [1];
			vertexTexCoords.push_back (glm::vec2 (atof (sd [0].c_str ()), atof (sd [1].c_str ())));
		} else if (type == "f") {
			ss >> sd [0] >> sd [1] >> sd [2];
			if (sd [0].find ("//") != sd [0].npos) {
				// POSITIONS AND NORMALS

				std::vector<std::string> indices;
				indices.resize (3);

				split (sd [0], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], glm::vec2 (), vertexNormals [atoi (indices [2].c_str ()) - 1]));

				split (sd [1], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], glm::vec2 (), vertexNormals [atoi (indices [2].c_str ()) - 1]));

				split (sd [2], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], glm::vec2 (), vertexNormals [atoi (indices [2].c_str ()) - 1]));
			} else if (sd [0].find ('/') == sd [0].npos) {
				// POSITIONS
				vertices.push_back (Vertex (vertexPositions [atoi (sd [0].c_str ()) - 1]));
			} else {
				// POSITIONS UVs AND NORMALS
				std::vector<std::string> indices;
				indices.resize (3);

				split (sd [0], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], vertexTexCoords [atoi (indices [1].c_str ()) - 1], vertexNormals [atoi (indices [2].c_str ()) - 1]));

				split (sd [1], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], vertexTexCoords [atoi (indices [1].c_str ()) - 1], vertexNormals [atoi (indices [2].c_str ()) - 1]));

				split (sd [2], '/', indices);
				vertices.push_back (Vertex (vertexPositions [atoi (indices [0].c_str ()) - 1], vertexTexCoords [atoi (indices [1].c_str ()) - 1], vertexNormals [atoi (indices [2].c_str ()) - 1]));
			}
		}
	}

	objectFile.close ();

	return Model (vertices);
	*/
}