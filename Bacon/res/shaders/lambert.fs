#version 400

in vec3 pass_position;
in vec2 pass_texCoord;
in vec3 pass_normal;
uniform sampler2D diffuse;
uniform vec3 ambient;
uniform vec4 lightPosition;
uniform vec3 lightColour;
out vec4 out_colour;

void main () {
	vec3 finalColour = ambient;

	if (lightPosition.w == 1.0) {
		vec3 delta = pass_position - lightPosition.xyz;
		finalColour += lightColour / dot (delta, delta);
	} else
		finalColour += max (dot (pass_normal, lightPosition.xyz), 0.0) * lightColour;

	out_colour = texture (diffuse, pass_texCoord) * vec4 (finalColour, 1.0);
}