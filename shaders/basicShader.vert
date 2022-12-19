#version 330 core

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

// Fog
float u_FogDensity = 0.07;
float u_FogGradient = 1.0;
out float visibility;

out vec3 color;
out vec3 normals;
out vec2 texCoords;

void main() {
	color = u_color;
	texCoords = a_uv;
	normals = normalize((u_m_trans * vec4(a_normals,0.0)).xyz);


	// ------ Fog ------
	vec4 worldPosition = u_m_trans * vec4(a_position, 1.0);
	vec4 positionRelativeCam = u_view_matrix * worldPosition;
	float distance = length(positionRelativeCam.xyz);

	visibility = exp(-pow((distance*u_FogDensity),u_FogGradient));
	visibility = clamp(visibility,0.0,1.0);
	
	
	gl_Position = (u_vp_matrix*u_m_trans) * vec4(a_position, 1);
}