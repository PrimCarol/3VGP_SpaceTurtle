
#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_color;

uniform mat4 u_m_trans;

out vec3 color;

void main() {
	color = a_color;
	gl_Position = u_m_trans * vec4(a_position, 1);	
}