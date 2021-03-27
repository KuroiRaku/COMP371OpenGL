#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;

uniform mat4 vm;
uniform mat4 pm;
uniform mat4 mm;
uniform mat4 light_view_proj_matrix;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec4 fragment_position_light_space;

//Texture
out vec2 v_TexCoord;

void main()
{
	fragment_normal = mat3(transpose(inverse(mm))) * normals;
	fragment_position = vec3(mm * vec4(position, 1.0f));
	fragment_position_light_space = light_view_proj_matrix * vec4(fragment_position, 1.0);
	gl_Position = pm * vm * mm * vec4(position, 1.0);

	//Texture
	v_TexCoord = vec2(position);

}