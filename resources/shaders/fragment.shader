#version 330 core

out vec4 result_color;


//For Shadows
uniform vec3 light_direction;

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


uniform vec3 spotlight_color3;
uniform vec3 spotlight_position3;
uniform vec3 spotlight_direction3;

uniform float spotlight_cutoff3;
uniform float spotlight_outer_cutoff3;
uniform float spotlight_constant3;
uniform float spotlight_linear3;
uniform float spotlight_quadratic3;
uniform bool spotlight_on3;

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
uniform bool shadow_on; 

in vec3 fragment_position; //interpolated
in vec3 normal;

in vec4 fragment_position_light_space;
uniform sampler2D shadow_map;
in vec4 gl_FragCoord;

flat in vec3 col;

//Texture
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

//const
const float ambient_strength = 0.55f;
const float diffuse_strength = 0.85f;
const float specular_strength = 1.0f;

// function declaration.
vec3 calculate_spotlight(float shadow_arg);
vec3 calculate_spotlight2(float shadow_arg);
vec3 calculate_spotlight3(float shadow_arg);

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
	// calculate bias (based on depth map resolution and slope)
	vec3 normal_s = normalize(normal);
	vec3 lightDir = normalize(light_position - fragment_position);
	float bias = max(0.05 * (1.0 - dot(normal_s, light_direction)), 0.005);
	// check whether current frag pos is in shadow
	// float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
	// PCF
	float shadow = 0.0;
	return ((current_depth - bias) > closest_depth) ? 1.0 : 0.0;
	
	//vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
	//for (int x = -1; x <= 1; ++x)
	//{
	//	for (int y = -1; y <= 1; ++y)
	//	{
	//		float pcfDepth = texture(shadow_map, normalized_device_coordinates.xy + vec2(x, y) * texelSize).r;
	//		shadow += ((current_depth - bias) > pcfDepth) ? 1.0 : 0.0;
	//	}
	//}


	//// keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
	//if (normalized_device_coordinates.z > 1.0)
	//	shadow = 0;

	//return shadow;
}

void main()
{

	//ambient
	float scalar = shadow_scalar();

	if (shadow_on == true)
	{
		scalar = shadow_scalar();
	}
	else
	{
		scalar = 0.2;
	}

	vec3 ambient = ambient_strength * light_color;

	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	  //use max so that it doesn't go negative
	vec3 diffuse = diffuse_strength * max(dot(normalize(normal), light_direction), 0.0) * light_color;

	//Specular
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 halfway_direction = normalize(light_direction + view_direction);
	vec3 reflect_light_direction = reflect(-light_direction, normalize(normal));

	vec3 specular = scalar * specular_strength * pow(max(dot(reflect_light_direction, halfway_direction), 0.0), 32) * light_color;

	vec3 color = (ambient + (1.0 - scalar) * (diffuse + specular)) * object_color;

	vec3 spotlight = calculate_spotlight(scalar);

	vec3 spotlight2 = calculate_spotlight2(scalar);

	vec3 spotlight3 = calculate_spotlight3(scalar);
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



	if (spotlight_on3) {
		result_color = vec4(spotlight3 * texColor.rgb, 1.0f);
	}
	else if (spotlight_on) {
		result_color = vec4(spotlight * texColor.rgb, 1.0f);

	}
	else if (spotlight_on2) {
		result_color = vec4(spotlight2 * texColor.rgb, 1.0f);

	} else if (!spotlight_on3&& !spotlight_on2&& !spotlight_on){
		result_color = vec4(color * texColor.rgb, 1.0f) + texColor;
	}


}


vec3 calculate_spotlight(float shadow_arg)
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
	vec3 diffuse = shadow_arg * diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + (1.0 - shadow_arg) * (diffuse + specular)) * object_color;
}

vec3 calculate_spotlight2(float shadow_arg)
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
	vec3 diffuse = shadow_arg * diffuse_strength * max(dot(normal, light_direction), 0.0) * spotlight_color2;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color2;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + (1.0 - shadow_arg) * (diffuse + specular)) * object_color;
}

vec3 calculate_spotlight3(float shadow_arg)
{
	vec3 light_direction = normalize(spotlight_position3 - fragment_position);
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_direction = reflect(-light_direction, normal);

	// attenuation
	float distance = length(spotlight_position3 - fragment_position);
	float attenuation = 1.0 / (spotlight_constant2 + spotlight_linear2 * distance + spotlight_quadratic2 * (distance * distance));
	// spotlight intensity
	vec3 halfway_direction = normalize(light_direction + view_direction);
	float theta = dot(light_direction, normalize(-spotlight_direction3));
	float epsilon = spotlight_cutoff2 - spotlight_outer_cutoff2;
	float intensity = clamp((theta - spotlight_outer_cutoff2) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = ambient_strength * spotlight_color3;
	vec3 diffuse = shadow_arg * diffuse_strength * max(dot(normal, halfway_direction), 0.0) * spotlight_color3;
	vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * spotlight_color3;

	ambient *= ambient_strength * attenuation * intensity;
	diffuse *= diffuse_strength * attenuation * intensity;
	specular *= specular_strength * attenuation * intensity;

	return (ambient + (1.0 - shadow_arg) * (diffuse + specular)) * object_color;
}
