#version 330
layout (location=0) in vec3 a_position;

uniform mat4 u_m_trans;
uniform vec3 u_color;

out vec3 color;

void main() {
	color = u_color;
	gl_Position = u_m_trans * vec4(a_position, 1);	
}