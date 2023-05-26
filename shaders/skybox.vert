#version 330 core

layout (location = 0) in vec3 a_position;

layout (location = 5) in mat4 instance_Matrix;

out vec3 TexCoords;

uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

void main(){
    TexCoords = a_position;
    vec4 pos = u_vp_matrix * instance_Matrix * vec4(a_position, 1.0);
    gl_Position = pos.xyww;
} 