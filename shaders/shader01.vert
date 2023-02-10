#version 330

// Mesh
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

// Basic Info
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

uniform mat4 u_m_trans;
uniform vec4 u_color;

// Fog
uniform float u_FogDensity;
uniform float u_FogGradient;
out float visibility;


// Basic Out
out vec4 color;
out vec3 normals;
out vec3 modelPosition;
out vec2 texCoords;

void main(){
	color = u_color;

	texCoords = a_uv;

	modelPosition = (u_m_trans * vec4(a_position,1)).xyz;
	normals = normalize((u_m_trans * vec4(a_normal,0.0)).xyz);

	gl_Position = (u_vp_matrix*u_m_trans) * vec4(a_position, 1);

	// ------ Fog ------
	vec4 worldPosition = u_m_trans * vec4(a_position, 1.0);
	vec4 positionRelativeCam = u_view_matrix * worldPosition;
	float distance = length(positionRelativeCam.xyz);

	//visibility = exp(-pow((distance*u_FogDensity),u_FogGradient));
	visibility = exp(-pow((distance*0.05),10.0));
	visibility = clamp(visibility,0.0,1.0);
}