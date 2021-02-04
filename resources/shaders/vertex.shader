#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;

uniform mat4 vm;
uniform mat4 pm;
uniform mat4 mm;

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
uniform bool green;
uniform bool blue;

out vec3 fragment_position;
out vec3 normal;

flat out vec3 col;

uniform mat4 projection;

void main()
{
	normal = mat3(transpose(inverse(mm))) * normals;
	fragment_position = vec3(mm * vec4(position, 1.0f));
	gl_Position = pm * vm * mm * vec4(position, 1.0);

	//ambient
	float ambient_strength = 0.25f;
	vec3 ambient = ambient_strength * light_color;

	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	float diffuse_strength = 0.75f; //use max so that it doesn't go negative
	vec3 diffuse = diffuse_strength * max(dot(normalize(normal), light_direction), 0.0) * light_color;

	//Specular
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflect_light_direction = reflect(-light_direction, normalize(normal));
	float specular_strength = 1.0f;
	vec3 specular = specular_strength * pow(max(dot(reflect_light_direction, view_direction), 0.0), 32) * light_color;

	//Gouraud
	if (flag == true) {

		//Without Lighting
		if (lights == true) {
			if (normalcol == true) {
				col = normal;
			}
			else {
				col = ambient * object_color;
			}
		}
		//With Lighting
		else {
			if (normalcol == true) {
				col = (specular + diffuse + ambient) * normal;
			}
			else {
				col = (specular + diffuse + ambient) * object_color;
				if (red == true) {
					if (col.x != ((specular + diffuse + ambient) * object_color).x) {
						col.x = ((specular + diffuse + ambient) * object_color).x;
					}
					else
						col.x = 0;
				}

				if (green == true) {
					if (col.y != ((specular + diffuse + ambient) * object_color).y) {
						col.y = ((specular + diffuse + ambient) * object_color).y;
					}
					else
						col.y = 0;
				}

				if (blue == true) {
					if (col.z != ((specular + diffuse + ambient) * object_color).z) {
						col.z = ((specular + diffuse + ambient) * object_color).z;
					}
					else
						col.z = 0;
				}

				if (colour == true) {
					if (col != (specular + diffuse + ambient) * object_color) {
						col = (specular + diffuse + ambient) * object_color;
					}
				}
			}
		}
	}
}