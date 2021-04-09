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


// SpotLight.
uniform vec3 spotlight_color2;
uniform vec3 spotlight_position2;
uniform vec3 spotlight_direction2;

uniform float spotlight_cutoff2;
uniform float spotlight_outer_cutoff2;
uniform float spotlight_constant2;
uniform float spotlight_linear2;
uniform float spotlight_quadratic2;
uniform bool spotlight_on2;

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
vec3 calculate_spotlight2();

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

	vec3 color = (specular + diffuse + ambient) * object_color;

	vec3 spotlight = calculate_spotlight();

	vec3 spotlight2 = calculate_spotlight2();
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


	
	if (spotlight_on2 && spotlight_on) {

		result_color = vec4(color * texColor.rgb+ spotlight2 * texColor.rgb+ spotlight * texColor.rgb, 1.0f);
	}
	else if (spotlight_on) {

		result_color = vec4(color * texColor.rgb, 1.0f) + vec4(spotlight * texColor.rgb, 1.0f);

	}
	else if (spotlight_on2) {
		result_color = vec4(color * texColor.rgb, 1.0f) + vec4(spotlight2 * texColor.rgb, 1.0f);

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

vec3 calculate_spotlight2()
{
	vec3 light_direction = normalize(spotlight_position2 - fragment_position);
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_direction = reflect(-light_direction, normal);

	// attenuation
	float distance = length(spotlight_position - fragment_position);
	float attenuation = 1.0 / (spotlight_constant2 + spotlight_linear2 * distance + spotlight_quadratic2 * (distance * distance));
	// spotlight intensity
	float theta = dot(light_direction, normalize(-spotlight_direction2));
	float epsilon = spotlight_cutoff2 - spotlight_outer_cutoff2;
	float intensity = clamp((theta - spotlight_outer_cutoff2) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = ambient_strength * spotlight_color2;
	vec3 diffuse = diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color2;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color2;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + diffuse + specular) * object_color;
}