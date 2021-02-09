#version 330 core
layout(location = 0) in vec3 position;   // the position variable has attribute position 0
layout(location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader
uniform mat4 vm;
uniform mat4 pm;
uniform mat4 mm;
out vec3 fragment_position;

void main()
{
    fragment_position = vec3(mm * vec4(position, 1.0f));
    gl_Position = pm * vm * mm * vec4(position, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}
