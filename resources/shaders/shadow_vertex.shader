#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 mm;
uniform mat4 pvm;


void main() {
	gl_Position = pvm * mm * vec4(position, 1.0);
}