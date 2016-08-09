#version 400

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 colour_interp;
in vec2 uv_interp;

// Attributes passed with the material file
uniform sampler2D skybox_map;

void main() 
{
	vec4 pixel = texture(diffuse_map, uv_interp);

	vec4 fragColor = pixel;

	gl_FragColor = fragColor;
}