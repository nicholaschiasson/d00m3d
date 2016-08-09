#version 400

// Attributes passed from the geometry shader
in vec2 tex_coord;

// Attributes passed with the material file
uniform vec4 particle_colour;
uniform sampler2D tex_samp;


void main (void)
{
	// Apply texture and color it according to the color supplied in the material file
	vec4 outval = texture(tex_samp, tex_coord);
    outval = vec4(outval.r*particle_colour.r, outval.g*particle_colour.g, outval.b*particle_colour.b, sqrt(sqrt(outval.r)));
	gl_FragColor = outval;
}