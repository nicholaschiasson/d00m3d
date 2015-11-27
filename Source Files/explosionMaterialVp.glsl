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

// Attributes forwarded to the geometry shader
out vec4 particle_colour;
out float particle_id;


void main()
{
	particle_id = colour.r;
    // Let time cycle every four seconds
	float circtime = timer - 7.0 * floor(timer / 7);
	float t = circtime; // Our time parameter
	// Settings for the explosion
	// Could also define these in the material file to have multiple particle systems with different settings
    float grav = 0.05; // Gravity
    float slow = 1; // Allows to slow down the explosion, control the speed of the explosion
	float velocity = 1 - grav*t*2;
	velocity = max(velocity, 0);
	// Let's first work in model space (apply only world matrix)
	vec4 position = world_mat * vec4(vertex, 1.0);
	vec4 norm = normal_mat * vec4(normal, 1.0);

    // Move point along normal and down with t*t (acceleration under gravity)
    position.x +=  norm.x*t*slow*velocity - grav*slow*up_vec.x*t*t;
    position.y += norm.y*t*slow*velocity - grav*slow*up_vec.y*t*t;
    position.z += norm.z*t*slow*velocity - grav*slow*up_vec.z*t*t;
	

	
	// Now apply view transformation
	gl_Position = view_mat * position;
	    
	// Define color of vertex
	particle_colour = vec4(1,1,1,1); // Uniform color assigned in material file
}
