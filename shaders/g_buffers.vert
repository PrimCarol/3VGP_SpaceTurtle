#version 330 core

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

layout (location = 3) in mat4 instance_Matrix;
layout (location = 7) in vec4 instance_Color;
layout (location = 8) in ivec2 instance_TexIndex; // Texture Atlas
layout (location = 9) in float instance_MatRoughness;
layout (location = 10) in float instance_MatMetallic;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out float Roughness;
out float Metallic;

out vec4 color;

// Basics
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

//Texture Atlas
uniform int rows;
uniform int cols;
uniform int sizeTileX;
uniform int sizeTileY;

void main(){

	// ----- UV's and Atlas ------
	float row = instance_TexIndex.y % rows;
	float column = instance_TexIndex.x % cols;

	float atlas_width = sizeTileX*cols;
	float atlas_height = sizeTileY*rows;
	float offset_width = 0.5 / atlas_width;
	float offset_height = 0.5 / atlas_height;
	
	float tempUVx = a_uv.x;
	float tempUVy = a_uv.y;

	if(cols > 1){	tempUVx = tempUVx < 0.5 ? offset_width : (1 - offset_width); }

	vec2 tempUV = vec2((tempUVx/cols) + (column / cols), (tempUVy/rows) + (row / rows));
	TexCoords = tempUV;
    //TexCoords = a_uv;
	// ----------------------

	Roughness = instance_MatRoughness;
	Metallic = instance_MatMetallic;

    vec4 worldPos = instance_Matrix * vec4(a_position, 1.0);
    FragPos = worldPos.xyz;
    
    color = instance_Color;

    mat3 normalMatrix = transpose(inverse(mat3(instance_Matrix)));
    Normal = normalMatrix * a_normal;

    gl_Position = u_projection_matrix * u_view_matrix * worldPos;
}  