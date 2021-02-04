#shader vertex 
#version 330 core

out vec4 result_color;

//uniform vec3 light_colors;
//uniform vec3 light_position;
uniform vec3 object_color;
uniform vec3 view_position;

uniform bool add_lights;
uniform bool spot_light;

in vec3 fragment_position; //interpolated
in vec3 normal;
in vec4 fragment_position_lightspace;
uniform sampler2D shadowMap;

//in vec3 col;

struct PointLight {
	vec3 position;
	vec3 color;
};

struct SpotLight {
	vec3  position;
	vec3 color;
	vec3 direction;
	float cutOff;
};

vec3 ComputePointLight(PointLight light, vec3 norm, vec3 fragment_pos, vec3 view_dir, vec3 object_col) {

	//ambient
	float ambient_strength = 0.25f;

	//diffuse
	vec3 light_direction = normalize(light.position - fragment_pos);
	float diffuse_strength = 0.75f;

	//Specular
	vec3 reflect_light_direction = reflect(-light_direction, normalize(norm));
	float specular_strength = 1.0f;

	//computing lights
	vec3 ambient = ambient_strength * light.color;
	vec3 diffuse = diffuse_strength * max(dot(normalize(norm), light_direction), 0.0) * light.color;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_dir), 0.0), 32) * light.color;

	vec3 color = (ambient + diffuse + specular) * object_col;

	return color;
}

float shadow_calc(vec4 frag_pos_light, vec3 light_dir) {

	vec3 projCoords = frag_pos_light.xyz / frag_pos_light.w;
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow
	float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);
	float shadow = (currentDepth - bias) > closestDepth ? 1.0 : 0.0;

	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

vec3 ComputeSpotLight(SpotLight light, vec3 norm, vec3 fragment_pos, vec3 view_dir, vec3 object_col) {
	//ambient
	float ambient_strength = 0.25f;

	//diffuse
	vec3 light_direction = normalize(light.position - fragment_pos);
	float diffuse_strength = 0.75f;

	//Specular
	vec3 reflect_light_direction = reflect(-light_direction, normalize(norm));
	float specular_strength = 1.0f;

	//computing lights
	vec3 ambient = ambient_strength * light.color;
	vec3 diffuse = diffuse_strength * max(dot(normalize(norm), light_direction), 0.0) * light.color;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_dir), 0.0), 32) * light.color;

	//computing shadows
	float shadow = shadow_calc(fragment_position_lightspace, light_direction);

	float theta = dot(light_direction, normalize(-light.direction));

	vec3 color;

	if (theta > light.cutOff)
	{
		color = (ambient + (1.0 - shadow) * (diffuse + specular)) * object_col;
	}
	else  // else, use ambient light so scene isn't completely dark outside the spotlight.
		color = ambient * object_col;

	return color;
}

#define NR_POINT_LIGHTS 5
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform SpotLight spotLight;

void main()
{
	vec3 view_direction = normalize(view_position - fragment_position);

	if (spot_light == false && add_lights == false) {
		vec3 color;
		color = ComputePointLight(pointLights[0], normal, fragment_position, view_direction, object_color);
		result_color = vec4(color, 1.0f);
	}
	else if (add_lights == true) {
		vec3 color;
		for (int i = 1; i < NR_POINT_LIGHTS; i++) {
			color += ComputePointLight(pointLights[i], normal, fragment_position, view_direction, object_color);
		}
		result_color = vec4(color, 1.0f);
	}
	else if (spot_light == true) {
		vec3 color;
		color = ComputeSpotLight(spotLight, normal, fragment_position, view_direction, object_color);
		result_color = vec4(color, 1.0f);
	}






	/*
	vec3 color = (specular + diffuse + ambient) * object_color;

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
	}*/
}


#shader fragment
#version 330 core

out vec4 result_color;

//uniform vec3 light_colors;
//uniform vec3 light_position;
uniform vec3 object_color;
uniform vec3 view_position;

uniform bool add_lights;
uniform bool spot_light;

in vec3 fragment_position; //interpolated
in vec3 normal;
in vec4 fragment_position_lightspace;
uniform sampler2D shadowMap;

//in vec3 col;

struct PointLight {
	vec3 position;
	vec3 color;
};

struct SpotLight {
	vec3  position;
	vec3 color;
	vec3 direction;
	float cutOff;
};

vec3 ComputePointLight(PointLight light, vec3 norm, vec3 fragment_pos, vec3 view_dir, vec3 object_col) {

	//ambient
	float ambient_strength = 0.25f;

	//diffuse
	vec3 light_direction = normalize(light.position - fragment_pos);
	float diffuse_strength = 0.75f;

	//Specular
	vec3 reflect_light_direction = reflect(-light_direction, normalize(norm));
	float specular_strength = 1.0f;

	//computing lights
	vec3 ambient = ambient_strength * light.color;
	vec3 diffuse = diffuse_strength * max(dot(normalize(norm), light_direction), 0.0) * light.color;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_dir), 0.0), 32) * light.color;

	vec3 color = (ambient + diffuse + specular) * object_col;

	return color;
}

float shadow_calc(vec4 frag_pos_light, vec3 light_dir) {

	vec3 projCoords = frag_pos_light.xyz / frag_pos_light.w;
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow
	float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);
	float shadow = (currentDepth - bias) > closestDepth ? 1.0 : 0.0;

	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

vec3 ComputeSpotLight(SpotLight light, vec3 norm, vec3 fragment_pos, vec3 view_dir, vec3 object_col) {
	//ambient
	float ambient_strength = 0.25f;

	//diffuse
	vec3 light_direction = normalize(light.position - fragment_pos);
	float diffuse_strength = 0.75f;

	//Specular
	vec3 reflect_light_direction = reflect(-light_direction, normalize(norm));
	float specular_strength = 1.0f;

	//computing lights
	vec3 ambient = ambient_strength * light.color;
	vec3 diffuse = diffuse_strength * max(dot(normalize(norm), light_direction), 0.0) * light.color;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_dir), 0.0), 32) * light.color;

	//computing shadows
	float shadow = shadow_calc(fragment_position_lightspace, light_direction);

	float theta = dot(light_direction, normalize(-light.direction));

	vec3 color;

	if (theta > light.cutOff)
	{
		color = (ambient + (1.0 - shadow) * (diffuse + specular)) * object_col;
	}
	else  // else, use ambient light so scene isn't completely dark outside the spotlight.
		color = ambient * object_col;

	return color;
}

#define NR_POINT_LIGHTS 5
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform SpotLight spotLight;

void main()
{
	vec3 view_direction = normalize(view_position - fragment_position);

	if (spot_light == false && add_lights == false) {
		vec3 color;
		color = ComputePointLight(pointLights[0], normal, fragment_position, view_direction, object_color);
		result_color = vec4(color, 1.0f);
	}
	else if (add_lights == true) {
		vec3 color;
		for (int i = 1; i < NR_POINT_LIGHTS; i++) {
			color += ComputePointLight(pointLights[i], normal, fragment_position, view_direction, object_color);
		}
		result_color = vec4(color, 1.0f);
	}
	else if (spot_light == true) {
		vec3 color;
		color = ComputeSpotLight(spotLight, normal, fragment_position, view_direction, object_color);
		result_color = vec4(color, 1.0f);
	}






	/*
	vec3 color = (specular + diffuse + ambient) * object_color;

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
	}*/
}