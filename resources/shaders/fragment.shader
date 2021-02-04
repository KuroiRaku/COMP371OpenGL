#version 330 core

out vec4 result_color;

uniform vec3 light_color;
uniform vec3 light_position;
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

void main()
{

	//ambient
	float ambient_strength = 0.25f;
	vec3 ambient = ambient_strength * light_color;

	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	float diffuse_strength = 0.75f;  //use max so that it doesn't go negative
	vec3 diffuse = diffuse_strength * max(dot(normalize(normal), light_direction), 0.0) * light_color;

	//Specular
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_light_direction = reflect(-light_direction, normalize(normal));
	float specular_strength = 1.0f;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_direction), 0.0), 32) * light_color;

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
	}
}