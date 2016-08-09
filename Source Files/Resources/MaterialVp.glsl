#version 400

// Attributes passed automatically by OGRE
in vec3 vertex;
in vec3 normal;
in vec4 colour;

// Attributes passed with the material file
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 normal_mat;
uniform vec3 light_position;

// Attributes forwarded to the fragment shader
out vec4 colour_interp;
out vec3 position_interp;
out vec3 normal_interp;
out vec3 light_pos;


void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);
	position_interp = vec3(view_mat * world_mat * vec4(vertex, 1.0));
    colour_interp = colour;
	normal_interp = vec3(normal_mat * vec4(normal, 0.0));
    light_pos = vec3(view_mat * vec4(light_position, 1.0));
}