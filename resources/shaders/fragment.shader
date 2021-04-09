#version 330 core

out vec4 result_color;

// PointLight
uniform vec3 light_color;
uniform vec3 light_position;

// SpotLight.
uniform vec3 spotlight_color;
uniform vec3 spotlight_position;
uniform vec3 spotlight_direction;

uniform float spotlight_cutoff;
uniform float spotlight_outer_cutoff;
uniform float spotlight_constant;
uniform float spotlight_linear;
uniform float spotlight_quadratic;
uniform bool spotlight_on;

// Spotlight Rotate
uniform vec3 spotlight_color_rot;
uniform vec3 spotlight_position_rot;
uniform vec3 spotlight_direction_rot;

uniform float spotlight_cutoff_rot;
uniform float spotlight_outer_cutoff_rot;
uniform float spotlight_constant_rot;
uniform float spotlight_linear_rot;
uniform float spotlight_quadratic_rot;
uniform bool spotlight_rotate_on;

// General Lighting.
uniform vec3 object_color;
uniform vec3 view_position;
uniform bool colour;
uniform bool flag;
uniform bool lights;
uniform bool normalcol;
uniform bool greyscale;
uniform bool red;
uniform bool blue;
uniform bool green;

// Sheeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeesh
uniform vec3 spotlight_color_mod;
uniform vec3 spotlight_position_mod;
uniform vec3 spotlight_direction_mod;

uniform float spotlight_cutoff_mod;
uniform float spotlight_outer_cutoff_mod;
uniform float spotlight_constant_mod;
uniform float spotlight_linear_mod;
uniform float spotlight_quadratic_mod;
uniform bool spotlight_models_on;

in vec3 fragment_position; //interpolated
in vec3 normal;

flat in vec3 col;

//Texture
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

//const 
const float ambient_strength = 0.25f;
const float diffuse_strength = 0.75f;
const float specular_strength = 1.0f;

// function declaration.
vec3 calculate_spotlight();
vec3 calculate_spotlight_rotation();
vec3 calculate_spotlight_models();

void main()
{

	//ambient
	
	vec3 ambient = ambient_strength * light_color;

	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	  //use max so that it doesn't go negative
	vec3 diffuse = diffuse_strength * max(dot(normalize(normal), light_direction), 0.0) * light_color;

	//Specular
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_light_direction = reflect(-light_direction, normalize(normal));
	
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_direction), 0.0), 32) * light_color;

	vec3 color = (specular + diffuse + ambient); //* object_color;

	vec3 spotlight = calculate_spotlight();
	vec3 spotlight_rotate = calculate_spotlight_rotation();
	vec3 spotlight_models = calculate_spotlight_models();

	//Texture
	vec4 texColor = texture(u_Texture, v_TexCoord);
	//result_color = texColor;


	
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

	//Gouraud
	if (flag == true) {
		if (normalcol == true) {
			if (greyscale == true) {
				float grey = dot(col, vec3(0.2989, 0.5870, 0.1140));
				result_color = vec4(grey, grey, grey, 1.0f);
			}
			else
				result_color = vec4(col, 1.0f);
		}
		else {
			if (greyscale == true) {
				float grey = dot(col, vec3(0.2989, 0.5870, 0.1140));
				result_color = vec4(grey, grey, grey, 1.0f);
			}
			else
				result_color = vec4(col, 1.0f);
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
				color = normal;
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
				color = (specular + diffuse + ambient) * normal;
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

	vec4 spotlight_vec = spotlight_on ? vec4(spotlight * texColor.rgb, 1.0f) : vec4(0,0,0,0);
	vec4 spotlight_rotate_vec = spotlight_rotate_on ? vec4(spotlight_rotate * texColor.rgb, 1.0f) : vec4(0, 0, 0, 0);
	vec4 spotlight_models_vec = spotlight_models_on ? vec4(spotlight_models * texColor.rgb, 1.0f) : vec4(0, 0, 0, 0);

	if (spotlight_rotate_on || spotlight_on || spotlight_models_on) {
		result_color = vec4(color * texColor.rgb, 1.0f) + spotlight_vec + spotlight_rotate_vec + spotlight_models_vec;
	}
	else {
		result_color = vec4(color, 1.0f) + texColor;
	}
	
}


vec3 calculate_spotlight()
{
	vec3 light_direction = normalize(spotlight_position - fragment_position);
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_direction = reflect(-light_direction, normal);

	// attenuation
	float distance = length(spotlight_position - fragment_position);
	float attenuation = 1.0 / (spotlight_constant + spotlight_linear * distance + spotlight_quadratic * (distance * distance));
	// spotlight intensity
	float theta = dot(light_direction, normalize(-spotlight_direction));
	float epsilon = spotlight_cutoff - spotlight_outer_cutoff;
	float intensity = clamp((theta - spotlight_outer_cutoff) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = ambient_strength * spotlight_color;
	vec3 diffuse = diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + diffuse + specular) * object_color;
}

vec3 calculate_spotlight_rotation()
{
	vec3 light_direction = normalize(spotlight_position_rot - fragment_position);
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_direction = reflect(-light_direction, normal);

	// attenuation
	float distance = length(spotlight_position - fragment_position);
	float attenuation = 1.0 / (spotlight_constant_rot + spotlight_linear_rot * distance + spotlight_quadratic_rot * (distance * distance));
	// spotlight intensity
	float theta = dot(light_direction, normalize(-spotlight_direction_rot));
	float epsilon = spotlight_cutoff_rot - spotlight_outer_cutoff_rot;
	float intensity = clamp((theta - spotlight_outer_cutoff_rot) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = ambient_strength * spotlight_color_rot;
	vec3 diffuse = diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color_rot;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color_rot;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + diffuse + specular) * object_color;
}

vec3 calculate_spotlight_models()
{
	vec3 light_direction = normalize(spotlight_position_mod - fragment_position);
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_direction = reflect(-light_direction, normal);

	// attenuation
	float distance = length(spotlight_position - fragment_position);
	float attenuation = 1.0 / (spotlight_constant_mod + spotlight_linear_mod * distance + spotlight_quadratic_mod * (distance * distance));
	// spotlight intensity
	float theta = dot(light_direction, normalize(-spotlight_direction_mod));
	float epsilon = spotlight_cutoff_mod - spotlight_outer_cutoff_mod;
	float intensity = clamp((theta - spotlight_outer_cutoff_mod) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = ambient_strength * spotlight_color_mod;
	vec3 diffuse = diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color_mod;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color_mod;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + diffuse + specular) * object_color;
}