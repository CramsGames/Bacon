#pragma once

#include <glm\glm.hpp>

struct Vertex {
public:
	Vertex (glm::vec3 position = glm::vec3 (), glm::vec2 texcoord = glm::vec2 (), glm::vec3 normal = glm::vec3 ());

	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
};