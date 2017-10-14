#version 400

in vec3 position;
in vec2 texCoord;
in vec3 normal;
uniform mat4 projection;
uniform mat4 transform;
out vec3 pass_position;
out vec2 pass_texCoord;
out vec3 pass_normal;

void main () {
	gl_Position = projection * transform * vec4 (position, 1.0);
	pass_position = (transform * vec4 (position, 1.0)).xyz;
	pass_texCoord = texCoord;
	pass_normal = (transform * vec4 (normal, 0.0)).xyz;
}