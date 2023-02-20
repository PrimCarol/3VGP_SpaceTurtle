#version 330

// Mesh
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;
// Instancing Transformations
layout (location = 3) in mat4 instance_Matrix;
layout (location = 7) in vec4 instance_Color;

// Basic Info
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

// Fog
uniform float u_FogDensity;
uniform float u_FogGradient;
out float visibility;

//Texture Atlas
uniform int rows;
uniform int cols;
uniform ivec2 texIndex;

// Basic Out
out vec4 color;
out vec3 normals;
out vec3 modelPosition;
out vec2 texCoords;

void main(){
	color = instance_Color;

	int indexX = 3;
	int indexY = 2;

	float row = texIndex.y % rows;
	float column = texIndex.x % cols;

	vec2 tempUV = vec2((a_uv.x/cols) + (column / cols), (a_uv.y/rows) + (row / rows));
	texCoords = tempUV;

	//texCoords = a_uv;

	modelPosition = (instance_Matrix * vec4(a_position,1)).xyz;
	normals = normalize((instance_Matrix * vec4(a_normal,0.0)).xyz);

	gl_Position = u_vp_matrix * vec4(modelPosition,1.0);

	
	// ------ Fog ------
	vec4 worldPosition = instance_Matrix * vec4(a_position, 1.0);
	vec4 positionRelativeCam = u_view_matrix * worldPosition;
	float distance = length(positionRelativeCam.xyz);

	//visibility = exp(-pow((distance*u_FogDensity),u_FogGradient));
	
	visibility = exp(-pow((distance*0.0),10.0)); // <---- 0.05 good fog
	visibility = clamp(visibility,0.0,1.0);
}