#version 400

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 colour_interp;
in vec3 light_pos;

//attributes passed in from vertex shader
uniform vec4 ambient_colour;
uniform vec4 diffuse_colour;
uniform vec4 specular_colour;
uniform float phong_exponent;

void calculate_light(in vec3 light_pos, inout float Id, inout float Is)
{

	// Phong shading

	vec3 N, // Interpolated normal for fragment
	     L, // Light-source direction
		 V, // View direction
		 R; // Refelction Vector

	// Compute Lambertian lighting Id
    N = normalize(normal_interp);

	L = (light_pos - position_interp);
	L = normalize(L);

	Id += max(dot(N, L), 0.0);
	
	// Compute specular term for Phong shading
	// Initially: V = (eye_position - position_interp);
	V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    R = -L + 2 *dot(L, N) * N; // Halfway vector
    R = normalize(R);

    float spec_angle_cos = max(dot(N, R), 0.0);
	Is += pow(spec_angle_cos, phong_exponent);
}

void main() 
{
	float Id =0;
	float Is = 0;

	vec4 light_colour = vec4(0,0,0,0);
	vec4 black = vec4(0,0,0,1);

	calculate_light(light_pos, Id, Is);

	if(colour_interp == black){
		light_colour = ambient_colour + Id*diffuse_colour + Is*specular_colour;
	}else{
		light_colour = colour_interp + Id*colour_interp + Is*colour_interp;
	}
	
	gl_FragColor = light_colour;
}

