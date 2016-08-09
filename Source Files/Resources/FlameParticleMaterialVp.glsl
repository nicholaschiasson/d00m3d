#version 400

// Attributes passed automatically by OGRE
in vec3 vertex;
in vec3 normal;
in vec4 colour;

// Attributes passed with the material file
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform vec3 up_vec;
uniform float timer;
uniform float duration;

// Attributes forwarded to the geometry shader
out vec4 vertex_colour;
out float particle_id;

// Define some useful constants
const float pi = 3.1415926536;
const float pi_over_two = 1.5707963268;
const float two_pi = 2.0*pi;


void main()
{
    // Define particle id
	particle_id = colour.r; // Derived from the particle colour. We use the id to keep track of particles

    float phase = two_pi*particle_id; // Start the sin wave later depending on the particle_id
	float param = timer / 0.25 + phase; // The constant that divides "timer" adjusts the "speed" of the fire
	float rem = mod(param, pi_over_two); // Use the remainder of dividing by pi/2 so that we are always in the range [0..pi/2] where sin() gives values in [0..1]
	float circtime = sin(rem); // Get time value in [0..1], according to a sinusoidal wave
	
	// Settings for the explosion
    float t = abs(circtime)*(0.3 + abs(normal.y)); // Our time parameter
    float accel = 1.2; // An acceleration applied to the particles coming from some attraction force
    float slow = 2.0; // Allows us to slow down the motion, control its speed
	

    // Move point along normal and down with t*t (acceleration under gravity)
	
	vec3 pos = vertex + slow*normal*accel*t*t; // Particle moves up

	// Let's first work in model space (apply only world matrix)
	vec4 position = world_mat * vec4(pos, 1.0);
	vec4 norm = normal_mat * vec4(normal, 1.0);
	
	// Now apply view transformation
	gl_Position = view_mat * position;
	    
	// Define color of vertex
	float alpha = 1.0 - circtime / duration;
	vertex_colour = vec4(1.0, 1.0, 1.0, alpha);
}
