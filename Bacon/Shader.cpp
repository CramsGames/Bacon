#include "stdafx.h"
#include "Shader.h"
#include <iostream>
#include <fstream>

static void CheckShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader (const std::string& fileName);
static GLuint CreateShader (const std::string& text, GLenum shaderType);

Shader::Shader (const std::string& fileName, unsigned char shaders)
	: shaders (shaders) {
	_program = glCreateProgram ();

	if (shaders & VERTEX_F) {
		_shaders [VERTEX_S] = CreateShader (LoadShader (fileName + ".vs"), GL_VERTEX_SHADER);
		glAttachShader (_program, _shaders [VERTEX_S]);
	}
	if (shaders & GEOMETRY_F) {
		_shaders [GEOMETRY_S] = CreateShader (LoadShader (fileName + ".gs"), GL_GEOMETRY_SHADER);
		glAttachShader (_program, _shaders [GEOMETRY_S]);
	}
	if (shaders & FRAGMENT_F) {
		_shaders [FRAGMENT_S] = CreateShader (LoadShader (fileName + ".fs"), GL_FRAGMENT_SHADER);
		glAttachShader (_program, _shaders [FRAGMENT_S]);
	}

	glLinkProgram (_program);
	CheckShaderError (_program, GL_LINK_STATUS, true, "Error: Program linking failed");

	glValidateProgram (_program);
	CheckShaderError (_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
}

Shader::~Shader () {
	if (shaders & VERTEX_F) {
		glDetachShader (_program, _shaders [VERTEX_S]);
		glDeleteShader (_shaders [VERTEX_S]);
	}
	if (shaders & GEOMETRY_F) {
		glDetachShader (_program, _shaders [GEOMETRY_S]);
		glDeleteShader (_shaders [GEOMETRY_S]);
	}
	if (shaders & FRAGMENT_F) {
		glDetachShader (_program, _shaders [FRAGMENT_S]);
		glDeleteShader (_shaders [FRAGMENT_S]);
	}
	glDeleteProgram (_program);
}

void Shader::Bind () {
	glUseProgram (_program);
}

static GLuint CreateShader (const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader (shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed" << std::endl;

	const GLchar* shaderSourceStrings [1];
	GLint shaderSourceStringLengths [1];

	shaderSourceStrings [0] = text.c_str ();
	shaderSourceStringLengths [0] = (GLint)text.length ();

	glShaderSource (shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader (shader);

	CheckShaderError (shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}

static std::string LoadShader (const std::string& fileName) {
	std::ifstream file;
	file.open ((fileName).c_str ());

	std::string output;
	std::string line;

	if (file.is_open ()) {
		while (file.good ()) {
			getline (file, line);
			output.append (line + "\n");
		}
	} else {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

static void CheckShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error [1024] = {0};

	if (isProgram)
		glGetProgramiv (shader, flag, &success);
	else
		glGetShaderiv (shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog (shader, sizeof (error), NULL, error);
		else
			glGetShaderInfoLog (shader, sizeof (error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}