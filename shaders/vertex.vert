#version 330

// Vertex Info
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normals;
layout (location=2) in vec2 a_uv;

// Camera
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

// Object info
uniform mat4 u_m_trans;
uniform vec3 u_color;

out vec3 color;
out vec3 normals;
out vec2 texCoords;

out vec3 modelPosition;

void main() {
	color = u_color;

	normals = normalize((u_m_trans * vec4(a_normals,0.0)).xyz);
	texCoords = a_uv;

	gl_Position = (u_vp_matrix * u_m_trans) * vec4(a_position, 1);	
}