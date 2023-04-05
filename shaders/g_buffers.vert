#version 330 core

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

layout (location = 3) in mat4 instance_Matrix;
layout (location = 7) in vec4 instance_Color;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

out vec4 color;

uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

void main(){
    vec4 worldPos = instance_Matrix * vec4(a_position, 1.0);
    FragPos = worldPos.xyz; 
    TexCoords = a_uv;
    
    color = instance_Color;

    mat3 normalMatrix = transpose(inverse(mat3(instance_Matrix)));
    Normal = normalMatrix * a_normal;

    gl_Position = u_projection_matrix * u_view_matrix * worldPos;
}  