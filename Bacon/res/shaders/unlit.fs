#version 400

in vec2 pass_texCoord;
uniform sampler2D diffuse;
out vec4 out_colour;

void main () {
	out_colour = texture (diffuse, pass_texCoord);
}