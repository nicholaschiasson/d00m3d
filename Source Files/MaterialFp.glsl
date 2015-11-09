#version 400

// Attributes passed from the vertex shader
in vec4 colour_interp;

//attributes passed in from vertex shader
uniform vec4 default_colour;

void main() 
{
	vec4 black = vec4(0,0,0,1);
	if(colour_interp == black){
		gl_FragColor = default_colour;
	}else{
		gl_FragColor = colour_interp;
	}
}