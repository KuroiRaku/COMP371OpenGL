#version 330 core

const float PI = 3.1415926535897932384626433832795;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 light_direction;

uniform vec3 object_color;

const float shading_ambient_strength = 0.25;
const float shading_diffuse_strength = 0.75;
const float shading_specular_strength = 0.3;

uniform float light_cutoff_outer;
uniform float light_cutoff_inner;
uniform float light_near_plane;
uniform float light_far_plane;

uniform vec3 view_position;

uniform sampler2D shadow_map;

in vec3 fragment_position; //interpolated
in vec4 fragment_position_light_space;
in vec3 fragment_normal;

in vec4 gl_FragCoord;

//Texture
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

// some gimmicks
uniform bool colour;
uniform bool flag;
uniform bool lights;
uniform bool normalcol;
uniform bool greyscale;
uniform bool red;
uniform bool blue;
uniform bool green;

out vec4 result_color;

float shadow_scalar() {
	// this function returns 1.0 when the surface receives light, and 0.0 when it is in a shadow
	// perform perspective divide
	vec3 normalized_device_coordinates = fragment_position_light_space.xyz / fragment_position_light_space.w;
	// transform to [0,1] range
	normalized_device_coordinates = normalized_device_coordinates * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragment_position_light_space as coords)
	float closest_depth = texture(shadow_map, normalized_device_coordinates.xy).r;
	// get depth of current fragment from light's perspective
	float current_depth = normalized_device_coordinates.z;
	// check whether current frag pos is in shadow
	float bias = 0;  // bias applied in depth map: see shadow_vertex.glsl
	return ((current_depth - bias) < closest_depth) ? 1.0 : 0.0;
}

float spotlight_scalar() {
	float theta = dot(normalize(fragment_position - light_position), light_direction);

	if (theta > light_cutoff_inner) {
		return 1.0;
	}
	else if (theta > light_cutoff_outer) {
		return (1.0 - cos(PI * (theta - light_cutoff_outer) / (light_cutoff_inner - light_cutoff_outer))) / 2.0;
	}
	else {
		return 0.0;
	}
}

void main()
{
	//scalar 
	float scalar = shadow_scalar() * spotlight_scalar();

	//ambient
	vec3 ambient = shading_ambient_strength * light_color;

	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	vec3 diffuse = scalar * shading_diffuse_strength * max(dot(normalize(fragment_normal), light_direction), 0.0) * light_color;

	//Specular
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_light_direction = reflect(-light_direction, normalize(fragment_normal));
	vec3 specular = shading_specular_strength * pow(max(dot(reflect_light_direction, view_direction), 0.0), 32) * light_color;

	vec3 color = (specular + diffuse + ambient) * object_color;

	//Texture
	vec4 texColor = texture(u_Texture, v_TexCoord);
	result_color = texColor * vec4(color,1.0f);
	
	if (red == true) {
		if (color.x != ((specular + diffuse + ambient) * object_color).x) {
			color.x = ((specular + diffuse + ambient) * object_color).x;
		}
		else
			color.x = 0;
	}

	if (green == true) {
		if (color.y != ((specular + diffuse + ambient) * object_color).y) {
			color.y = ((specular + diffuse + ambient) * object_color).y;
		}
		else
			color.y = 0;
	}

	if (blue == true) {
		if (color.z != ((specular + diffuse + ambient) * object_color).z) {
			color.z = ((specular + diffuse + ambient) * object_color).z;
		}
		else
			color.z = 0;
	}

	if (colour == true) {
		if (color != (specular + diffuse + ambient) * object_color) {
			color = (specular + diffuse + ambient) * object_color;
		}
	}

	//Phong
	else {
		//Without Lighting
		if (lights == true) {
			color = ambient * object_color;
			if (red == true) {
				if (color.x != (ambient * object_color).x) {
					color.x = (ambient * object_color).x;
				}
				else
					color.x = 0;
			}

			if (green == true) {
				if (color.y != (ambient * object_color).y) {
					color.y = (ambient * object_color).y;
				}
				else
					color.y = 0;
			}

			if (blue == true) {
				if (color.z != (ambient * object_color).z) {
					color.z = (ambient * object_color).z;
				}
				else
					color.z = 0;
			}

			if (normalcol == true) {
				color = fragment_normal;
				if (greyscale == true) {
					float grey = dot(color, vec3(0.2989, 0.5870, 0.1140));
					result_color = vec4(grey, grey, grey, 1.0f);
				}
				else
					result_color = vec4(color, 1.0f);
			}
			else {
				if (greyscale == true) {
					float grey = dot(color, vec3(0.2989, 0.5870, 0.1140));
					result_color = vec4(grey, grey, grey, 1.0f);
				}
				else {

					result_color = vec4(color, 1.0f);
				}
			}
		}
		//With Lighting
		else {
			if (normalcol == true) {
				color = (specular + diffuse + ambient) * fragment_normal;
				if (greyscale == true) {
					float grey = dot(color, vec3(0.2989, 0.5870, 0.1140));
					result_color = vec4(grey, grey, grey, 1.0f);
				}
				else
					result_color = vec4(color, 1.0f);
			}
			else {
				if (greyscale == true) {
					float grey = dot(color, vec3(0.2989, 0.5870, 0.1140));
					result_color = vec4(grey, grey, grey, 1.0f);
				}
				else {
					result_color = vec4(color, 1.0f);
				}
			}
		}
	}
	result_color = result_color + texColor;
}