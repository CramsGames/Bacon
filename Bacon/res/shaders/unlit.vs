#version 400

in vec3 position;
in vec2 texCoord;
uniform mat4 transform;
out vec2 pass_texCoord;

void main () {
	gl_Position = vec4 (transform * dvec4 (position, 1.0));
	pass_texCoord = texCoord;
}