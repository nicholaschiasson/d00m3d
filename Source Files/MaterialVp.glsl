#version 400

// Attributes passed automatically by OGRE
in vec3 vertex;
in vec4 colour;

// Attributes passed with the material file
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

// Attributes forwarded to the fragment shader
out vec4 colour_interp;


void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);

    colour_interp = colour;
}