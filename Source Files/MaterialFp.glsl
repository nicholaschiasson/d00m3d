#version 400

// Attributes passed from the vertex shader
in vec4 colour_interp;


void main() 
{
	gl_FragColor = colour_interp;
}