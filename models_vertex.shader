#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 vm;
uniform mat4 pm;
uniform mat4 mm;
out vec3 fragment_position;
out vec2 v_TexCoord;

void main()
{
    fragment_position = vec3(mm * vec4(position, 1.0f));
    gl_Position = pm * vm * mm * vec4(position, 1.0);
    v_TexCoord = texCoord;
}
